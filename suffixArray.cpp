#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
struct suffix{ // 用于第一种构造后缀数组的方式
    int index;
    char* suff;
};
struct suffix2{ // 用于第二种构造后缀数组的方式
    int index,rank[2];
};
bool cmp(const suffix &a,const suffix &b){
    return strcmp(a.suff,b.suff) < 0;
}
bool cmp2(const suffix2 &a,const suffix2 &b){
    return a.rank[0]==b.rank[0]?a.rank[1]<b.rank[1]:a.rank[0]<b.rank[0];
}
int* buildSuffix(char* text){
    // 构造后缀数组,O(n*n*lgn)
    int n = strlen(text);
    suffix suffixes[n];
    for(int i = 0;i < n;++i){
        suffixes[i].index = i;
        suffixes[i].suff = text+i;
    }
    sort(suffixes,suffixes+n,cmp);
    // suffixArr保存的后缀在text中的起始下标
    int *suffixArr = new int[n];
    for(int i = 0;i < n;++i) suffixArr[i] = suffixes[i].index;
    return suffixArr;
}
int* buildSuffix2(char* text){
    // 构造后缀数组,O(n*lgn*lgn)
    int n = strlen(text);
    suffix2 suffixes[n];
    // 构造初始状态，前两个字符
    for(int i = 0;i < n;++i){
        suffixes[i].index = i;
        suffixes[i].rank[0] = text[i]-'a';
        if(i+1 < n) suffixes[i].rank[1] = text[i+1]-'a';
        else suffixes[i].rank[1] = -1;
    }
    // 按照前两个字符排序
    sort(suffixes,suffixes+n,cmp2);
    int rank0[n]; // rank0[i]起始下标为i的后缀对应的rank[0]
    // 根据第i个后缀的前k/2个字符和紧接的后k/2个字符的排序结果，
    // 推测按照前k个字符排序的结果
    for(int k = 4;k < 2*n;k *= 2){
        // 对排序后的后缀重新赋值rank[0]
        int rank = 0,preRank = suffixes[0].rank[0];
        suffixes[0].rank[0] = 0;
        rank0[suffixes[0].index] = 0;
        for(int i = 1;i < n;++i){
            if(preRank==suffixes[i].rank[0] &&
               suffixes[i].rank[1]==suffixes[i-1].rank[1]){
                // 必须引入临时变量preRank,因为每一次会更改原来的suffixes[i].rank[0]
                preRank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else{
                preRank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            rank0[suffixes[i].index] = rank;
        }
        // 对排序后的后缀重新赋值rank[1]
        for(int i = 0;i < n;++i){
            int nextIndex = suffixes[i].index+k/2;
            suffixes[i].rank[1] = nextIndex < n ? rank0[nextIndex] : -1;
        }
        // 再按照rank[0],rank[1]排序
        sort(suffixes,suffixes+n,cmp2);
    }
    int *suffixArr = new int[n];
    for(int i = 0;i < n;++i)
        suffixArr[i] = suffixes[i].index;
    return suffixArr;
}
void printArr(int *suffixArr,int n){
    for(int i = 0;i < n;++i)
        printf("%d ", suffixArr[i]);
    printf("\n");
}
bool search(char* text,char* patt,int *suffixArr){
    // 根据后缀数组在text中二分查找patt
    int n = strlen(text),m = strlen(patt);
    int flag,mid,l = 0,r = n-1;
    while(l <= r){
        mid = l+(r-l>>1);
        flag = strncmp(text+suffixArr[mid],patt,m);
        if(!flag) return true;
        else if(flag < 0) l = mid+1;
        else r = mid-1;
    }
    return false;
}
int main(){
    char text[N],patt[N];
    while(~scanf("%s %s",text,patt)){
        int n = strlen(text);
        int *suffixArr = buildSuffix(text);
        int *suffixArr2 = buildSuffix2(text);
        printArr(suffixArr,n);
        printArr(suffixArr2,n);
        if(search(text,patt,suffixArr2))
            cout << "find " << patt << endl;
        else cout << "not find " << patt << endl;
        delete[] suffixArr;
        delete[] suffixArr2;
    }
    return 0;
}
