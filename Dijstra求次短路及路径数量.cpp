/**
Dijstra求次短路
hdu 3191
题意：给出一个带权（权值非负）有向图，
保证无环且两点之间至多有一条边，
求次短路的长度以及数量？
*/
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define N 55
#define M 2005
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
const int INF = 1<<30;
//dis[v][0]，dis[v][1]分别对应v到起点的最短路和次短路
//cnt[v][0]，cnt[v][1]分别对应v到起点的最短路和次短路的条数
//vis[v][0]，vis[v][1]分别对应v是否已经加入到最短路和次短路形成的树中来了
int n,m,head[N],ne,vis[N][2],dis[N][2],cnt[N][2];
struct Edge{
    int v,next,w;
}e[M];
void add_edge(int u,int v,int w){
    e[ne].v = v,e[ne].w = w;
    e[ne].next = head[u],head[u] = ne++;
}
//Node中的mask表示当前的点u是作为最短路还是次短路上的点
struct Node{
    int u,dis,mask;
    Node(){}
    Node(int u,int dis,int mask):u(u),dis(dis),mask(mask){}
    bool operator < (const Node &a)const{
        if(dis == a.dis) return u > a.u;
        return dis > a.dis;
    }
};
priority_queue<Node> q;
pii Dijstra(int s,int t){
    memset(vis,0,sizeof(vis));
    memset(cnt,0,sizeof(cnt));
    for(int i = 0;i <= n;i++)
        for(int j = 0;j < 2;j++) dis[i][j] = INF;
    while(!q.empty()) q.pop();
    cnt[s][0] = 1,vis[s][1] = 1,dis[s][0] = 0;
    q.push(Node(s,0,0));
    int u,v,w,next_dis,mask;
    while(!q.empty()){
        Node node = q.top();
        q.pop();
        u = node.u,mask = node.mask;
        if(vis[u][mask]) continue;
        vis[u][mask] = 1;
        for(int i = head[u];i != -1;i = e[i].next){
            v = e[i].v,w = e[i].w;
            next_dis = node.dis+w;
            if(!vis[v][0] && dis[v][0] > next_dis){
                if(dis[v][0] != INF){//已经找到过一条最短路，更新次短路
                    dis[v][1] = dis[v][0];
                    cnt[v][1] = cnt[v][0];
                    q.push(Node(v,dis[v][1],1));
                }
                dis[v][0] = next_dis;
                cnt[v][0] = cnt[u][mask];
                q.push(Node(v,dis[v][0],0));
            }
            else if(!vis[v][0] && dis[v][0] == next_dis){
                //注意这里不是加上cnt[u][0]，而是加上cnt[u][mask]
                cnt[v][0] += cnt[u][mask];
            }
            else if(!vis[v][1] && dis[v][1] > next_dis){
                dis[v][1] = next_dis;
                cnt[v][1] = cnt[u][mask];
                q.push(Node(v,dis[v][1],1));
            }
            else if(!vis[v][1] && dis[v][1] == next_dis){
                cnt[v][1] += cnt[u][mask];
            }
        }
    }
    return make_pair(dis[t][1],cnt[t][1]);
}
int main(){
    int u,v,w,s,t;
    while(~scanf("%d %d %d %d",&n,&m,&s,&t)){
        ne = 0;
        memset(head,-1,sizeof(head));
        for(int i = 0;i < m;i++){
            scanf("%d %d %d",&u,&v,&w);
            add_edge(u,v,w);
        }
        pii ans = Dijstra(s,t);
        printf("%d %d\n", ans.first,ans.second);
    }
    return 0;
}