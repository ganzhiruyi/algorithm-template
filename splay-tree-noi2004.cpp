#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 2e5+100;
const int inf = 1e9;
struct SplayTree{
	int val[N],son[N][2],pre[N];
	int size[N];      // size[x]表示x子树有多少个值，相同的值分开计算
	int cnt[N];       // cnt[x]表示在树中，当前节点x的值val[x]有多少个
	int tree_size,rt; // tree_size代表整棵树的节点个数，rt是树的根
	int newNode(int y,int v){
		int x = ++tree_size;
		val[x] = v,pre[x] = y,cnt[x] = size[x] = 1;
		son[x][0] = son[x][1] = 0;
		return x;
	}
	void init(){
		tree_size = 0;
		rt = 0;
		val[0] = son[0][0] = son[0][1] = pre[0] = cnt[0] = size[0] = 0;
	}
	void pushUp(int x){
		size[x] = size[son[x][0]] + size[son[x][1]] + cnt[x];
	}
	void rotate(int x,int c){ // c=0 for zag, c=1 for zig
		int y = pre[x];
		son[y][!c] = son[x][c];
		pre[son[x][c]] = y;
		pre[x] = pre[y];
		if(pre[y])
			son[pre[y]][son[pre[y]][1]==y] = x;
		son[x][c] = y;
		pre[y] = x;
		pushUp(y); // only need update y, the father of x.
	}
	void splay(int x,int goal){ // rotate the subtree x as goal's son
		while(pre[x] != goal){
			if(pre[pre[x]] == goal){
				if(son[pre[x]][0] == x)
					rotate(x,1);
				else
					rotate(x,0);
			}
			else{
				int y = pre[x],z = pre[y];
				if(son[z][0] == y){
					if(son[y][0] == x)
						rotate(y,1),rotate(x,1);
					else
						rotate(x,0),rotate(x,1);
				}
				else{
					if(son[y][0] == x)
						rotate(x,1),rotate(x,0);
					else
						rotate(y,0),rotate(x,0);
				}
			}
		}
		pushUp(x); // only update the x, the y will be updated in rotate. 
		if(goal == 0) rt = x;
	}
	void insert(int x,int fa,int v){
		// 注意这里是与根相同则不新增加节点，只是增加cnt[x]
		if(!x){
			x = newNode(fa,v);
			son[fa][v>val[fa]] = x;
			splay(x,0);
			return;
		}
		if(val[x] == v){
			++cnt[x];
			++size[x];
			splay(x,0);
			return;
		}
		else if(val[x] > v)
			insert(son[x][0],x,v);
		else
			insert(son[x][1],x,v);
		pushUp(x);
	}

	int del_subtree(int x,int limit){
		if(!x) return 0;
		int ret = 0;
		if(val[x] >= limit)
			ret += del_subtree(son[x][0],limit);
		else{
			ret += size[son[x][0]]+cnt[x]; // 删除x节点和x的左子树
			int y = pre[x];
			son[x][0] = 0;
			pre[son[x][1]] = y;
			if(y)
				son[y][son[y][1]==x] = son[x][1];
			if(!y) rt = son[x][1]; //如果x是根节点，更新rt
			x = son[x][1];
			ret += del_subtree(x,limit);
		}
		if(x) pushUp(x);
		return ret;
	}
	int select_kth(int x,int k){
		// 查找从小到大第k个元素
		if(k <= size[son[x][0]])
			return select_kth(son[x][0],k);
		else if(k > size[son[x][0]]+cnt[x])
			return select_kth(son[x][1],k-size[son[x][0]]-cnt[x]);
		else{
			splay(x,0); // 把x旋转到根,因为查询次数多，放到根更快，但是发现去掉之后也没慢多少
			return val[x];
		}
	}
	void preorder(int x){
		if(!x) return;
		printf("rt:%d, pre:%d,val_pre:%d,cur: %d size:%d,val:%d ---- left: %d size: %d,val:%d, right: %d,size:%d,val:%d\n", 
			rt,pre[x],val[pre[x]],x,size[x],val[x],
			son[x][0],size[son[x][0]],val[son[x][0]],
			son[x][1],size[son[x][1]],val[son[x][1]]);
		preorder(son[x][0]);
		preorder(son[x][1]);
	}
}spt;
int main(){
	int n,m,a,w,ans;
	char op[4];
	int limit; // 表示当前的边界是多少
	scanf("%d %d",&n,&m);
	while(~scanf("%d %d",&n,&m)){
		w = 0; // record the salary change, add a: w+a, sub a: w-a.
		spt.init();
		ans = 0;
		for(int i = 0;i < n;i++){
			scanf("%s%d",op,&a);
			if(op[0] == 'I'){
				a -= w;
				if(a >= m-w) spt.insert(spt.rt,0,a);
			}
			else if(op[0] == 'A'){
				w += a;
			}
			else if(op[0] == 'S'){
				w -= a;
				limit = m-w;
				ans += spt.del_subtree(spt.rt,limit);
			}
			else{
				int sz = spt.size[spt.rt];
				// printf("size:%d\n",spt.size[spt.rt]);
				if(a == 0 || a > sz)
					printf("-1\n");
				else{
					// 把求n个数中的第k大转化成求从小到大第n-k+1个
					printf("%d\n", spt.select_kth(spt.rt,sz-a+1)+w);
				}
			}
			// printf("%d***************************\n", i);
			// spt.preorder(spt.rt);	
		}
		printf("%d\n", ans);
	}
	return 0;
}