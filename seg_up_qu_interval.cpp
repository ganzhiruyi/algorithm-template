#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;
typedef long long ll;
const int N = 100005;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
struct Node{
	int lazy,l,r;
	ll sum;
}node[N<<2];
int val[N];
void pushUp(int rt){
	node[rt].sum = node[ls].sum + node[rs].sum;
}
void pushDown(int rt){
	int lazy = node[rt].lazy;
	if(lazy != -1){
		node[ls].lazy = node[rs].lazy = lazy;
		node[ls].sum = (ll)lazy*(node[ls].r-node[ls].l+1);
		node[rs].sum = (ll)lazy*(node[rs].r-node[rs].l+1);
		node[rt].lazy = -1;
	}
}
void build(int rt,int l,int r){
	node[rt].l = l,node[rt].r = r,node[rt].lazy = -1;
	if(l == r){
		node[rt].sum = val[l];
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushUp(rt);
}
void update(int rt,int L,int R,int v){
	int l = node[rt].l,r = node[rt].r;
	if(L <= l && r <= R){
		node[rt].lazy = v;
		node[rt].sum = (ll)v*(r-l+1);
		return;
	}
	pushDown(rt);
	if(L <= mid) update(ls,L,R,v);
	if(R > mid) update(rs,L,R,v);
	pushUp(rt);
}
ll query(int rt,int L,int R){
	int l = node[rt].l,r = node[rt].r;
	if(L <= l && r <= R){
		return node[rt].sum;
	}
	ll res = 0;
	pushDown(rt);
	if(L <= mid) res += query(ls,L,R);
	if(R > mid) res += query(rs,L,R);
	return res; 
}

int main(){
	int n,m,L,R,v,op,rt = 1;
	cin >> n;
	for(int i = 0;i < n;i++) cin >> val[i];
	build(rt,0,n-1);
	cin >> m;
	for(int i = 0;i < m;i++){
		cin >> op >> L >> R;
		L--,R--;
		if(op){
			cin >> v;
			update(rt,L,R,v);
		}
		else cout << query(rt,L,R) << endl;
	}
	return 0;
}