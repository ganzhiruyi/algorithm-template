#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
template<typename T>
class Node{
public:
	Node *left,*right;
	T value;
	Node(T v):value(v),left(NULL),right(NULL){}	
};
template<typename T>
class Splay_tree{
public:
	typedef Node<T> NodeType;
	NodeType *root;
	Splay_tree():root(NULL){}
	bool find(T key){
		root = splay_bottom_up(root,key);
		return root != NULL && root->value == key;
	}
	void pre_order(){
		printf("pre_order: ");
		pre_order_dfs(root);
		printf("\n");
	}
	bool insert(T key){
		// if tree is empty
		if(root == NULL){
			root = new NodeType(key);
			return true;
		}
		root = splay_bottom_up(root,key);
		if(root->value == key) return false; // already has value of key
		NodeType *x = new NodeType(key);
		if(root->value > key){
			// If root's key is greater, make root as right child
    		// of x and copy the left child of root to x
			x->left = root->left;
			root->left = NULL;
			x->right = root;
		}
		else{
			// If root's key is smaller, make root as left child
    		// of x and copy the right child of root to x
			x->right = root->right;
			root->right = NULL;
			x->left = root;
		}
		root = x;
		return true;
	}
	NodeType* find_pre(T key){
		// find value that before key
		if(!find(key)) return NULL;
		if(root->left == NULL) return NULL;
		NodeType *x = root->left;
		while(x->right) x = x->right;
		return x;
	}
	NodeType* find_next(T key){
		// find value that after key
		if(!find(key)) return NULL;
		if(root->right == NULL) return NULL;
		NodeType *x = root->right;
		while(x->left) x = x->left;
		return x;
	}
	NodeType* findMin(){
		// find the min value in tree.
		if(root == NULL) return NULL;
		NodeType *x = root;
		while(x->left != NULL) x = x->left;
		return (root = splay_bottom_up(root,x->value));
	}
	NodeType* findMax(){
		// find the max value in tree.
		if(root == NULL) return NULL;
		NodeType *x = root;
		while(x->right != NULL) x = x->right;
		return (root = splay_bottom_up(root,x->value));
	}
	NodeType* deleteMin(){
		// first findMin(), then left son of root must be NULL,
		// let right son of root be new root.
		// caller function is response for releasing the resource.
		if(root == NULL) return NULL;
		findMin();
		NodeType *tmp = root;
		root = root->right;
		return tmp;
	}
	NodeType* deleteMax(){
		// first findMax(), then right son of root must be NULL,
		// let left son of root be new root.
		// caller function is response for releasing the resource.
		if(root == NULL) return NULL;
		findMax();
		NodeType *tmp = root;
		root = root->left;
		return tmp;
	}
	bool delete_by_value(T key){
		// first find(key), this will let key to be the root.
		if(!find(key)) return false; // don't have the value.
		NodeType *L = root->left;
		NodeType *R = root->right;
		NodeType *tmp = root;
		// find the largest element in L;
		root = L;
		root = findMax();
		if(root == NULL) root = R;
		else root->right = R;
		delete tmp; // release the source of old root.
		return true;
	}
private:
	void pre_order_dfs(NodeType *root){
		if(root == NULL) return;
		printf("%d ", root->value);
		pre_order_dfs(root->left);
		pre_order_dfs(root->right);
	}
	NodeType* leftRotate(NodeType* x){
		// zag
		NodeType *y = x->right;
		x->right = y->left;
		y->left = x;
		return y;
	}
	NodeType* rightRotate(NodeType* x){
		// zig
		NodeType *y = x->left;
		x->left = y->right;
		y->right = x;
		return y;
	}
	NodeType* splay_bottom_up(NodeType *root, T key){
		/*
		This function brings the key at root if key is present in tree.
		If key is not present, then it brings the last accessed item at
		root.  This function modifies the tree and returns the new root
		*/
		if(root == NULL || root->value == key) return root;
		// key lies in left subtree. 
		if(root->value > key){
			if(root->left == NULL) return root;
			// zig-zig(left left)
			if(root->left->value > key){
				// First recursively bring the key as root of left-left
				root->left->left = splay_bottom_up(root->left->left,key);
				// Do first zig rotation for root, second zig rotation is done after else
				root = rightRotate(root);
			}
			else if(root->left->value < key){ // zag-zig(left-right)
				// First recursively bring the key as root of left-right
				root->left->right = splay_bottom_up(root->left->right,key);
				// Do first zag rotation for root->left, second zig rotation is done after else
				if(root->left->right != NULL)
					root->left = leftRotate(root->left);	
			}
			// Do second zig rotation for root
			return root = root->left == NULL ? root : rightRotate(root);
		}
		else{ // key lies in right subtree.
			if(root->right == NULL) return root;
			// zig-zag(right left)
			if(root->right->value > key){
				// First recursively bring the key as root of right-left
				root->right->left = splay_bottom_up(root->right->left,key);
				// Do first zig rotation for root->right, second zig rotation is done after else
				if(root->right->left != NULL)
					root->right = rightRotate(root->right);
			}
			else if(root->right->value < key){ //zag-zag(right right)
				// First recursively bring the key as root of right-right
				root->right->right = splay_bottom_up(root->right->right,key);
				// Do first zag rotation for root, second zig rotation is done after else
				root = leftRotate(root);
			}
			// Do second zag rotation for root
			return root = root->right == NULL ? root : leftRotate(root);
		}
	}
};
int main(){
	int n,a;
	char op[10];
	Splay_tree<int> st;
	bool flag = false;
	while(1){
		printf("***********************\n");
		printf("1. insert\n");
		printf("2. find\n");
		printf("3. findMax\n");
		printf("4. findMin\n");
		printf("5. deleteMax\n");
		printf("6. deleteMin\n");
		printf("7. delete_by_value\n");
		printf("8. find_pre\n");
		printf("9. find_next\n");
		printf("q. quit\n");
		Node<int> *tmp = NULL;
		cin >> op;
		switch(op[0]){
		case '1':
			cin >> n;
			for(int i = 0;i < n;i++){
				cin >> a;
				st.insert(a);
			}
			break;
		case '2':
			cin >> a;
			st.find(a);
			break;
		case '3':
			st.findMax();
			break;
		case '4':
			st.findMin();
			break;
		case '5':
			tmp = st.deleteMax();
			if(tmp) delete tmp;
			break;
		case '6':
			tmp = st.deleteMin();
			if(tmp) delete tmp;
			break;
		case '7':
			cin >> a;
			st.delete_by_value(a);
			break;
		case '8':
			cin >> a;
			tmp = st.find_pre(a);
			if(tmp == NULL) printf("no pre of %d\n",a);
			else printf("pre of %d is : %d\n", a,tmp->value);
			break;
		case '9':
			cin >> a;
			tmp = st.find_next(a);
			if(tmp == NULL) printf("no next of %d\n",a);
			else printf("next of %d is : %d\n",a,tmp->value);
			break;
		default:
			flag = true;
			break;
		}
		if(flag) break;
		st.pre_order();
	}
	return 0;
}
