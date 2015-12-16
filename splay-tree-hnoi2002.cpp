#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 50005;
const int inf = 1e9; 
struct SplayTree{
	int pre[N],son[N][2],val[N];
	int size,rt;
	int newNode(int y,int v){
		// add a new Node who's father is y, value is v.
		int x = ++size;
		val[x] = v, pre[x] = y;
		son[x][0] = son[x][1] = 0;
		return x;
	}
	void init(){
		size = 0;
		rt = newNode(0,-inf); // add -inf as the left bound 
		son[rt][1] = newNode(rt,inf); // add inf as the right bound
	}
	void insert(int v){
		int x = rt;
		while(son[x][v > val[x]]) x = son[x][v > val[x]];
		int y = newNode(x,v);
		son[x][v > val[x]] = y;
		splay(y,0); // let the inserted node y be new root  
	}
	void rotate(int x,int c){ // c=0 for zag, c=1 for zig
		int y = pre[x];
		son[y][!c] = son[x][c];
		pre[son[x][c]] = y;
		pre[x] = pre[y];
		// judge y is left node or right node of pre[y], then replace with x
		if(pre[y]) son[pre[y]][son[pre[y]][1]==y] = x;
		son[x][c] = y;
		pre[y] = x;
	}
	void splay(int x,int goal){ 
		// splay subtree x, to make subtree x is son of goal.  
		while(pre[x] != goal){
			if(pre[pre[x]] == goal){
				// single zig or zag
				if(son[pre[x]][0] == x)
					rotate(x,1);
				else
					rotate(x,0);
			}
			else{
				int y = pre[x],z = pre[y];
				if(son[z][0] == y){
					if(son[y][0] == x) // left-left, zig-zig
						rotate(y,1),rotate(x,1);
					else //left-right, zag-zig
						rotate(x,0),rotate(x,1);

				}
				else{
					if(son[y][0] == x) // right-left, zig-zag
						rotate(x,1),rotate(x,0);
					else // right-right, zag-zag
						rotate(y,0),rotate(x,0);
				}
			}
		}
		// if goal == 0, x is the new root.
		if(goal == 0) rt = x;
	}
	int find_predecessor(int v){
		// find the max value among these nodes who's not greater than v
		int x = rt,max_val = -inf;
		while(x){
			if(v == val[x]) return v;
			if(v > val[x]) max_val = max(max_val,val[x]);
			if(v > val[x]) x = son[x][1]; 
			else x = son[x][0];
		}
		return max_val;
	}
	int find_successor(int v){
		// find the min value among these nodes who's not less than v
		int x = rt,min_val = inf;
		while(x){
			if(v == val[x]) return v;
			if(v < val[x]) min_val = min(min_val,val[x]);
			if(v < val[x]) x = son[x][0];
			else x = son[x][1];
		}
		return min_val; 
	}
};
int main(){
	int a,n,ans,pre,suc;
	scanf("%d",&n);
	SplayTree spt;
	spt.init();
	ans = 0;
	scanf("%d",&a);
	ans += a; // first day, the min is a.
	spt.insert(a);
	for(int i = 1;i < n;i++){
		if(scanf("%d",&a) == -1) a = 0;
		pre = spt.find_predecessor(a);
		suc = spt.find_successor(a);
		ans += min(abs(a-pre),abs(suc-a));
		spt.insert(a);
	}
	printf("%d\n", ans);
	return 0;
}