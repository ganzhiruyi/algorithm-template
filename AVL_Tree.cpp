// AVL树的实现版本1，这里只支持插入一个集合的数，不支持重复插入，可以认为是map的实现方式
#include <stdio.h>
#include <stdlib.h>
struct Node{
    int key,height;
    Node *left,*right;
};
int height(Node *x){ return x == NULL ? 0 : x->height; }
int max(int a, int b){ return a > b ? a : b; }

Node* newNode(int key){
    Node *x = (Node*)malloc(sizeof(Node));
    x->key = key,x->height = 1;
    x->left = x->right = NULL;
    return x;
}
// 右旋以x为根的子树，并返回新的树根
Node* rightRotate(Node *x){
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    // 更新高度
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}
// 左旋以x为根的子树，并返回新的树根
Node* leftRotate(Node *x){
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    // 更新高度
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}
// 获取节点x的平衡值（左儿子高度-右儿子高度）
int getBalance(Node *x){ return x == NULL ? 0 : height(x->left)-height(x->right); }
// 返回以rt为根节点的子树的最小值节点
Node* minValueNode(Node *rt){
    Node *x = rt;
    while(x->left) x = x->left;
    return x;
}
// 在以x为根的AVL树中插入键值为key的节点（设为p）,返回插入之后的新的树根
Node* insert(Node *x, int key){
    // 先执行BST插入
    if(x == NULL) return newNode(key);
    if(key < x->key) x->left = insert(x->left,key);
    else x->right = insert(x->right,key);
    // 更新高度
    x->height = max(height(x->left),height(x->right)) + 1;
    // 判断当前这个p的祖先节点x的平衡性
    int balance = getBalance(x);
    // 不平衡分为四种
    // case LL, 右旋x
    if(balance > 1 && key < x->left->key) return rightRotate(x);
    // case LR, 先左旋x的左儿子，再右旋x
    if(balance > 1 && key > x->left->key){
        x->left = leftRotate(x->left);
        return rightRotate(x);
    }
    // case RR, 左旋x
    if(balance < -1 && key > x->right->key) return leftRotate(x);
    // case RL, 先右旋x的右儿子，再左旋x
    if(balance < -1 && key < x->right->key){
        x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    // 如果x是平衡的,直接返回
    return x;
}
// 在以x为根的AVL树中删除键值为key的节点（设为p）,返回删除之后的新的树根
Node *deleteNode(Node *x,int key){
    // 先执行BST删除
    if(x == NULL) return NULL;
    if(key < x->key) x->left = deleteNode(x->left,key);
    else if(key > x->key) x->right = deleteNode(x->right,key);
    else{
        Node *temp;
        // 如果x存在一个或者0个子节点
        if(x->left || x->right){
            temp = x->left ? x->left : x->right;
            // 没有子节点
            if(temp == NULL){
                temp = x;
                x = NULL;
            }
            else{ // 有一个子节点temp
                *x = *temp; // 直接用子树temp替代x
            }
            free(temp);
        }
        else{ // x存在两个子节点
            // 选取x的后继节点temp作为新的根节点
            temp = minValueNode(x->right);
            x->key = temp->key; // 复制temp中的键值替换x 
            x->right = deleteNode(x->right,temp->key); // 因为temp移动到x，递归去掉temp节点
        }
    }
    if(x == NULL) return x; //这一句不能漏掉，因为删除之后以x为根的子树已空
    // 更新高度
    x->height = max(height(x->left),height(x->right)) + 1;
    // 判断当前这个p的祖先节点x的平衡性
    int balance = getBalance(x);
    // 不平衡分为四种
    // case LL, 右旋x
    if(balance > 1 && getBalance(x->left) >= 0) return rightRotate(x);
    // case LR, 先左旋x的左儿子，再右旋x
    if(balance > 1 && getBalance(x->left) < 0){
        x->left = leftRotate(x->left);
        return rightRotate(x);
    }
    // case RR, 左旋x
    if(balance < -1 && getBalance(x->right) < 0) return leftRotate(x);
    // case RL, 先右旋x的右儿子，再左旋x
    if(balance < -1 && getBalance(x->right) >= 0){
        x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    // 如果x是平衡的,直接返回
    return x;
}
void preorder(Node *x){
    if(x == NULL) return;
    printf("%d ", x->key);
    preorder(x->left);
    preorder(x->right);
}
void inorder(Node *x){
    if(x == NULL) return;
    inorder(x->left);
    printf("%d ", x->key);
    inorder(x->right);
}
int main(){
    Node *rt = NULL;
    rt = insert(rt,9);
    rt = insert(rt,5);
    rt = insert(rt,10);
    rt = insert(rt,0);
    rt = insert(rt,6);
    rt = insert(rt,11);
    rt = insert(rt,-1);
    rt = insert(rt,1);
    rt = insert(rt,2);
    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
    printf("\nAfter insert all data, preorder of the AVL tree is:\n");
    preorder(rt);
    printf("\nAfter insert all data, inorder of the AVL tree is:\n");
    inorder(rt);
    rt = deleteNode(rt,10);
    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */
    printf("\nAfter delete 10, preorder of the AVL tree is:\n");
    preorder(rt);
    printf("\nAfter delete 10, inorder of the AVL tree is:\n");
    inorder(rt);
    return 0;
}

