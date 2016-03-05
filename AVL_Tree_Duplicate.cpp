#include <stdio.h>
#include <stdlib.h>
struct Node{
    int key,height,count; // count记录节点对应的key值有多少个
    Node *left,*right;
};
int max(int a,int b){ return a > b ? a : b; }
int height(Node *x){ return x == NULL ? 0 : x->height; }
int getBalance(Node *x){ return x == NULL ? 0 : height(x->left)-height(x->right); }
Node* newNode(int key){
    Node *x = (Node*)malloc(sizeof(Node));
    x->key = key,x->height = 1,x->count = 1;
    x->left = NULL,x->right = NULL;
    return x;
}
Node* rightRotate(Node *x){
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}
Node* leftRotate(Node *x){
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
    return y;
}
// 返回以rt为根节点的子树的最小值节点
Node* minValueNode(Node *rt){
    if(rt == NULL) return NULL;
    Node *x = rt;
    while(x->left) x = x->left;
    return x;
}
Node* insert(Node *x, int key){
    if(x == NULL) return newNode(key);
    if(key < x->key) x->left = insert(x->left,key);
    else if(key > x->key) x->right = insert(x->right,key);
    else{
        ++x->count;
        return x;
    }
    x->height = max(height(x->left),height(x->right)) + 1;
    int balance = getBalance(x);
    if(balance > 1 && key < x->left->key) return rightRotate(x);
    if(balance > 1 && key > x->left->key){
        x->left = leftRotate(x->left);
        return rightRotate(x);
    }
    if(balance < -1 && key > x->right->key) return leftRotate(x);
    if(balance < -1 && key < x->right->key){
        x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    return x;
}
Node* deleteNode(Node *x, int key){
    if(x == NULL) return x;
    if(key < x->key) x->left = deleteNode(x->left,key);
    else if(key > x->key) x->right = deleteNode(x->right,key);
    else{
        if(x->count > 1){
            --x->count;
            return x; // 节点x仍然存在
        }
        Node *temp;
        if(x->left == NULL || x->right == NULL){
            temp = x->left ? x->left : x->right;
            if(temp) *x = *temp;
            else{
                temp = x;
                x = NULL;
            }
            free(temp);
        }
        else{
            temp = minValueNode(x->right);
            x->key = temp->key;
            x->right = deleteNode(x->right,temp->key);
        }
    }
    if(x == NULL) return NULL; //这一句不能漏掉，因为删除之后以x为根的子树已空
    x->height = max(height(x->left),height(x->right)) + 1;
    int balance = getBalance(x);
    if(balance > 1 && getBalance(x->left) >= 0) return rightRotate(x);
    if(balance > 1 && getBalance(x->left) < 0){
        x->left = leftRotate(x->left);
        return rightRotate(x);
    }
    if(balance < -1 && getBalance(x->right) < 0) return leftRotate(x);
    if(balance < -1 && getBalance(x->right) >= 0){
        x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    return x;
}
void preorder(Node *x){
    if(x == NULL) return;
    printf("%d(%d) ", x->key,x->count);
    preorder(x->left);
    preorder(x->right);
}
void inorder(Node *x){
    if(x == NULL) return;
    inorder(x->left);
    printf("%d(%d) ", x->key,x->count);
    inorder(x->right);
}
int main(){
    Node *rt = NULL;
    rt = insert(rt,9);
    rt = insert(rt,5);
    rt = insert(rt,10);
    rt = insert(rt,5);
    rt = insert(rt,9);
    rt = insert(rt,7);
    rt = insert(rt,17);
    /* The constructed AVL Tree would be
            9(2)
           /  \
          5(2) 10(1)
           \     \
            7(1)  17(1)
    */
    printf("\nAfter insert all data, preorder of the AVL tree is:\n");
    preorder(rt);
    printf("\nAfter insert all data, inorder of the AVL tree is:\n");
    inorder(rt);
    rt = deleteNode(rt,10);
    /* The AVL Tree after deletion of 10
            9(2)
           /  \
          5(2) 17(1)
           \     
            7(1)
    */
    printf("\nAfter delete 10, preorder of the AVL tree is:\n");
    preorder(rt);
    printf("\nAfter delete 10, inorder of the AVL tree is:\n");
    inorder(rt);
    rt = deleteNode(rt,5);
    /* The AVL Tree after deletion of 10
            9(2)
           /  \
          5(1) 17(1)
           \     
            7(1)
    */
    printf("\nAfter delete 5, preorder of the AVL tree is:\n");
    preorder(rt);
    printf("\nAfter delete 5, inorder of the AVL tree is:\n");
    inorder(rt);
    return 0;
}
