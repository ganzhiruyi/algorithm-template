#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int N = 1005;
const int M = 10005;
const int inf = 0x7fffffff;
struct Edge{
	int next,v,w;
}e[M<<1];
int n,ne,m,head[N],vis[N],dis[N];
void add_edge(int u,int v,int w){
	e[ne].v = v,e[ne].w = w;
	e[ne].next = head[u];
	head[u] = ne++;
}
queue<int> q;
int spfa(int st,int ed){
	while(!q.empty()) q.pop();
	memset(vis,0,sizeof(vis));
	for(int i = 0;i <= n;i++) dis[i] = inf;
	vis[st] = 1,dis[st] = 0;
	q.push(st);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = head[u];i != -1;i = e[i].next){
			int v = e[i].v,w = e[i].w;
			if(dis[v] > dis[u]+w){
				dis[v] = dis[u]+w;
				if(!vis[v]){
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
	return dis[ed];
}
int main(int argc, char const *argv[]){
	int s,t,u,v,w;
	while(cin >> n >> m >> s >> t){
		ne = 0;
		memset(head,-1,sizeof(head));
		for(int i = 0;i < m;i++){
			cin >> u >> v >> w;
			add_edge(u,v,w),add_edge(v,u,w); 
		}
		int ans = spfa(s,t);
		cout << ans << endl;
	}
	return 0;
}