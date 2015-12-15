#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;
const int N = 1000005;
#define ls (rt<<1)
#define rs (rt<<1|1)
int val[N];
struct Node{
	int l,r,minv;
}node[N<<2];
void pushUp(int rt){
	node[rt].minv = min(node[ls].minv,node[rs].minv);
}
void build(int rt,int L,int R){
	node[rt].l = L,node[rt].r = R;
	if(L == R){
		node[rt].minv = val[L];
		return;
	}
	int mid = (L+R) >> 1;
	build(ls,L,mid);
	build(rs,mid+1,R);
	pushUp(rt);
}
void update(int rt,int index,int value){
	int l = node[rt].l,r = node[rt].r;
	int mid = (l+r)>>1;
	if(l == r){
		node[rt].minv = value;
		return;
	}
	if(index <= mid) update(ls,index,value);
	else update(rs,index,value);
	pushUp(rt);
}
int query(int rt,int L,int R){
	int l = node[rt].l,r = node[rt].r;
	//这个优化不可少，不能直接把结束条件设为遍历到叶子节点
	if(L <= l && r <= R) return node[rt].minv;
	int mid = (l+r)>>1;
	if(L > mid) return query(rs,L,R);
	else if(R <= mid) return query(ls,L,R);
	return min(query(ls,L,mid),query(rs,mid+1,R));
}
int main(){
	int n,m,op,L,R;	
	scanf("%d",&n);
	for(int i = 0;i < n;i++) scanf("%d",&val[i+1]);
	build(1,1,n);
	scanf("%d",&m);
	for(int i = 0;i < m;i++){
		scanf("%d %d %d",&op,&L,&R);
		if(op) update(1,L,R);
		else printf("%d\n", query(1,L,R));
	}
	return 0;
}