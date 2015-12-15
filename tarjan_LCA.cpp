#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <map>
using namespace std;
const int inf = 1000005;
const int N = 40005;
const int M = N<<1;
typedef long long ll;
struct Edge{
    int v,w,next;
}e[M];
struct Query{
    int v,next;
}q[M];
pair<int,int> id[N];
int head[N],headq[N],ne,nq,vis[N],fa[N];
ll dis[N],ans[M];
void add_edge(int u,int v,int w){
    e[ne].v = v,e[ne].w = w;
    e[ne].next = head[u];
    head[u] = ne++;
}
void add_query(int u,int v){
    q[nq].v = v;
    q[nq].next = headq[u];
    headq[u] = nq++;
}
int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void tarjan(int u){
    int v,w;
    vis[u] = true;
    for(int i = headq[u];i != -1;i = q[i].next){
        v = q[i].v;
        if(vis[v]) ans[i] = dis[u]+dis[v]-2*dis[find(v)];
    }
    for(int i = head[u];i != -1;i = e[i].next){
        v = e[i].v,w = e[i].w;
        if(!vis[v]){
            dis[v] = dis[u]+w;
            tarjan(v);
            fa[v] = u; 
        }
    }
}
int main(){
    int T,n,m,u,v,w;
    cin >> T;
    while(T--){
        cin >> n >> m;
        for(int i = 0;i <= n;i++) fa[i] = i;
        ne = nq = 0;
        memset(head,-1,sizeof(head));
        memset(headq,-1,sizeof(headq));
        memset(vis,false,sizeof(vis));
        memset(dis,0,sizeof(dis));
        memset(ans,0,sizeof(ans));
        for(int i = 0;i < n-1;i++){
            cin >> u >> v >> w;
            add_edge(u,v,w),add_edge(v,u,w);
        }
        for(int i = 0;i < m;i++){
            cin >> u >> v;
            id[i] = make_pair(nq,nq+1);
            add_query(u,v),add_query(v,u);
        }
        dis[1] = 0;
        tarjan(1);
        for(int i = 0;i < m;i++){
            cout << max(ans[id[i].first],ans[id[i].second]) << endl;
        }
    }
    return 0;
}