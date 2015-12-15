#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 100005;
const int M = 1000005;
struct Edge{
	int u,v,w;
	Edge(int a=0,int b=0,int c=0){u=a,v=b,w=c;}
}e[M];
bool cmp(Edge a,Edge b){
	return a.w < b.w;
}
int ne,fa[N],rank[N];
int find(int x){
	return x == fa[x] ? x : fa[x]=find(fa[x]);
}
int main(){
	int n,m,u,v,w,ans;
	while(cin >> n >> m){
		ne = ans = 0;
		for(int i = 0;i < m;i++){
			cin >> u >> v >> w;
			e[ne++] = Edge(u,v,w);
		}
		sort(e,e+m,cmp);
		for(int i = 0;i <= n;i++) fa[i] = i,rank[i] = 0;
		for(int i = 0;i < m;i++){
			int x = find(e[i].u),y = find(e[i].v);
			if(x != y){
				if(rank[x] < rank[y]) fa[y] = x;
				else{
					if(rank[x] == rank[y]) rank[y]++;
					fa[x] = y;
				}
				ans += e[i].w;
			}
		}
		cout << ans << endl;
	}
	return 0;
}