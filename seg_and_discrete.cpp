#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
const int N = 100005;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
map<int,int> mp;
vector<int> v;
struct Segment
{
	int l,r,id;
}seg[N];
struct Node
{
	int l,r,cov;
}node[N*8];
void pushDown(int rt){
	if(node[rt].cov != -1){
		node[ls].cov = node[rs].cov = node[rt].cov;
		node[rt].cov = -1;
	}
}
void build(int rt,int l,int r){
	node[rt].l = l,node[rt].r = r,node[rt].cov = -1;
	if(l+1 == r) return;
	build(ls,l,mid);
	build(rs,mid,r);
}
void update(int rt,int L,int R,int idx){
	int l = node[rt].l,r = node[rt].r;
	if(L <= l && r <= R){
		node[rt].cov = idx;
		return;
	}
	pushDown(rt);
	//更新时注意
	if(R <= mid) update(ls,L,R,idx);
	else if(L >= mid) update(rs,L,R,idx);
	else update(ls,L,R,idx),update(rs,L,R,idx);
}
int ans,vis[N];
void query(int rt){
	//vis记录每张海报是否已经计算过
	if(node[rt].cov != -1){
		if(!vis[node[rt].cov]){
			ans++;
			vis[node[rt].cov] = 1;
		}
		return; //遇到统计过的，cov值为单一某个海报id的节点就及时返回，不必继续找下去
	}
	//添加到叶子节点终止的条件
	if(node[rt].l+1 == node[rt].r) return;
	query(ls);
	query(rs);
}

int main(){
	int n,L,cnt,l,r;
	cin >> n >> L;
	v.clear();
	mp.clear();
	ans = 0;
	memset(vis,0,sizeof(vis));
	for(int i = 0;i < n;i++){
		cin >> seg[i].l >> seg[i].r;
		seg[i].id = i;
		v.push_back(seg[i].l),v.push_back(seg[i].r);
	}
	sort(v.begin(),v.end());
	cnt = 0;
	for(int i = 0;i < v.size();i++){
		mp[v[i]] = cnt++;
		while(i+1 < v.size() && v[i] == v[i+1]) i++;
	}
	int rt = 1;
	build(rt,0,cnt-1);
	for(int i = 0;i < n;i++){
		l = mp[seg[i].l],r = mp[seg[i].r];
		update(rt,l,r,seg[i].id);
	}
	query(rt);
	cout << ans << endl;
	return 0;
}