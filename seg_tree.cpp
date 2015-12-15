#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int N = 100005;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
int value[N];
struct Node{
	int l,r,sum,add,set;
}node[N<<2];
void pushUp(int rt){
	node[rt].sum = node[ls].sum + node[rs].sum;
}
void pushDown(int rt){
	int add = node[rt].add,set = node[rt].set;
	//若rt同时存在add,set标记(不要忽略这种情况)，那么一定是先set后add
	//因为set标记会覆盖add标记，这点一定要注意。
	if(set != -1){
		node[ls].set = node[rs].set = set,node[ls].add = node[rs].add = 0;
		node[rt].add = 0,node[rt].set = -1;
		node[ls].sum = (node[ls].r-node[ls].l+1)*set;
		node[rs].sum = (node[rs].r-node[rs].l+1)*set;
	}
	if(add){
		node[ls].add += add,node[rs].add += add;
		node[rt].add = 0,node[rt].set = -1;
		node[ls].sum += (node[ls].r-node[ls].l+1)*add;
		node[rs].sum += (node[rs].r-node[rs].l+1)*add; 
	}
	
}
void build(int rt,int l,int r){
	node[rt].l = l,node[rt].r = r;
	//add = 0表示当前节点没有add标记，set = -1表示当前节点没有set标记
	node[rt].add = 0,node[rt].set = -1;
	if(l == r){
		node[rt].sum = value[l];
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushUp(rt);
}
void update(int rt,int L,int R,int mark,int val){
	int l = node[rt].l,r = node[rt].r;
	if(L <= l && r <= R){
		if(mark == 0){
			node[rt].sum += (r-l+1)*val;
			node[rt].add += val;
		}
		else{
			node[rt].sum = (r-l+1)*val;
			node[rt].add = 0,node[rt].set = val;
		}
		return;
	}
	pushDown(rt);
	if(L <= mid) update(ls,L,R,mark,val);
	if(R > mid) update(rs,L,R,mark,val);
	pushUp(rt);
}
int query(int rt,int L,int R){
	int l = node[rt].l,r = node[rt].r,res = 0;
	if(L <= l && r <= R) return node[rt].sum;
	pushDown(rt);
	if(L <= mid) res += query(ls,L,R);
	if(R > mid) res += query(rs,L,R);
	return res;
}
int main(){
	int n,m,L,R,t,v,rt = 1;
	scanf("%d %d",&n,&m);
	for(int i = 0;i <= n;i++) scanf("%d",&value[i]);
	build(rt,0,n);
	for(int i = 0;i < m;i++){
		scanf("%d %d %d %d",&t,&L,&R,&v);
		update(rt,L,R,t,v);
		printf("%d\n", query(rt,0,n));
	}
	return 0;
}