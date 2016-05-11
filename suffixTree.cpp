#include <bits/stdc++.h>
using namespace std;
const int MAXN = 256;
class SuffixTree{
public:
    typedef struct SuffixNode{
        SuffixNode *children[MAXN],*suffixLink;
        // 后缀的范围[start,END],end指向END，记录的是该节点和其父节点之间的边形成的后缀
        int start,*end;
        int suffixIndex; // 后缀的起始下标
        SuffixNode(){}
        SuffixNode(SuffixNode *rt,int st,int *ed){
            for(int i = 0;i < MAXN;++i) children[i] = NULL;
            suffixLink = rt; // 默认指向根节点
            start = st,end = ed;
            suffixIndex = -1;
        }
    }Node;
    // activeNode,activeEdge,activeLen共同标识了activePoint位置
    Node *activeNode;
    int activeLen;
    int activeEdge;
    int END; // 用于trick3,自动更新所有leaf的end值
    int remainingSuffixCnt;
    Node *lastNewInNode; // 在一个extension中前一个创建的内节点
    Node *rt; // 后缀树的根节点
    string text; // 用于构建后缀树的text
    string specialChar;
    void init(){
        // 构建根节点并初始化相应的值
        int *rtEnd = new int(-1);
        rt = new Node(NULL,-1,rtEnd);
        END = -1;
        activeNode = rt;
        activeLen = 0;
        activeEdge = -1;
        remainingSuffixCnt = 0;
        lastNewInNode = NULL;
        specialChar = "$";
    }
    Node* build(string s){
        // 线性时间构建后缀树
        init();
        text = s + specialChar; // 确保后缀树是一颗explicit suffix tree
        for(int i = 0;i < text.length();++i)
            extension(i);
        return rt;
    }
    int edgeLength(Node *u){
        return *(u->end) - u->start + 1;
    }
    bool walkDown(Node *u){
        // 判断是否需要跳过当前u节点,trick1 skip/count
        if(activeLen >= edgeLength(u)){
            activeEdge += edgeLength(u); // skip
            activeLen -= edgeLength(u);
            activeNode = u;
            return true;
        }
        else return false;
    }
    void extension(int pos){
        // 处理每一个extension
        ++remainingSuffixCnt;
        END = pos; // trick 3 for Rule1
        lastNewInNode = NULL;
        while(remainingSuffixCnt){
            if(activeLen==0) // for APCFALZ(active point create for activeLen = 0)
                activeEdge = pos;
            if(activeNode->children[text[activeEdge]] == NULL){
                // Rule2,创建一个新的leaf node
                activeNode->children[text[activeEdge]] = new Node(rt,pos,&END);
                /** 因为此时activeNode创建了一个叶节点，
                所以activeNode是内节点或者根节点，
                那么就应该把上一个新创建的内节点lastNewInNode
                的suffixLink指向当前的activeNode
                **/
                if(lastNewInNode != NULL){
                    lastNewInNode->suffixLink = activeNode;
                    // if(activeNode != rt) lastNewInNode = rt;
                    lastNewInNode = NULL;
                }
            }
            else{
                Node *next = activeNode->children[text[activeEdge]];
                if(walkDown(next)){
                    // 从新的activePoint(next)继续extension
                    continue;
                }
                else{
                    if(text[next->start+activeLen]==text[pos]){
                        if(lastNewInNode != NULL && activeNode != rt){
                            lastNewInNode->suffixLink = activeNode;
                            lastNewInNode = NULL;
                        }
                        // APCFER3
                        ++activeLen;
                        // Rule3 is a stopper,所以停止这个extension
                        break;
                    }
                    // Rule2,创建新的内节点和叶节点
                    int *splitEnd = new int();
                    *splitEnd = next->start+activeLen-1;
                    Node *splitNode = new Node(rt,next->start,splitEnd);
                    activeNode->children[text[activeEdge]] = splitNode;
                    // 创建新的叶节点,splitNode是其父节点
                    splitNode->children[text[pos]] = new Node(rt,pos,&END);
                    next->start += activeLen;
                    splitNode->children[text[next->start]] = next; 

                    if(lastNewInNode != NULL){
                        lastNewInNode->suffixLink = splitNode;
                    }
                    // splitNode成为新的lastNewInNode
                    lastNewInNode = splitNode;
                }
            }
            // 一旦添加了新的suffix到后缀树中
            --remainingSuffixCnt;
            if(activeNode == rt && activeLen > 0){
                // APCFER2C1
                --activeLen;
                activeEdge = pos-remainingSuffixCnt+1;
            }
            else if(activeNode != rt){
                // APCFER2C2
                activeNode = activeNode->suffixLink;
            }
        }
    }
    void setSuffixIndexByDFS(Node *u,int height = 0){
        if(u == NULL) return;
        if(u->start != -1){
            // u不是根节点
            for(int i = u->start;i <= *(u->end);++i)
                printf("%c", text[i]);
        }
        bool isleaf = true;
        for(int i = 0;i < MAXN;++i){
            if(u->children[i]){
                if (isleaf && u->start != -1)
                    printf(" [%d]\n", u->suffixIndex);
                isleaf = false;
                setSuffixIndexByDFS(u->children[i],height+edgeLength(u->children[i]));
            }
        }
        if(isleaf){
            int index = text.length()-height;
            printf(" [%d]\n", index);
            u->suffixIndex = index;
        }
    }
    void freeSuffixTreeByPostOrder(Node *u){
        if(u == NULL) return;
        for(int i = 0;i < MAXN;++i){
            if(u->children[i])
                freeSuffixTreeByPostOrder(u->children[i]);
        }
        if(u->suffixIndex == -1) // 如果u是内节点，还要删除新建的end指针
            delete u->end;
        delete u; 
    }
};
int main(){
    string text = "abcabxabcd";
    SuffixTree tree;
    SuffixTree::Node *rt = tree.build(text);
    tree.setSuffixIndexByDFS(rt);
    tree.freeSuffixTreeByPostOrder(rt);
    return 0;
}
