#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
/*
http://hihocoder.com/contest/hiho34/problem/1
思路：先将点按照染色的思想分成左右两组，然后按照匈牙利算法计算
注意：由于匈牙利算法只统一根据从左到右的边或者从右到左的边，然后
计算出最大匹配,还有两个重要结论
1、最小点覆盖 = 最大二分匹配数
2、最大独立点集 = 顶点总数 - 最大二分匹配数
*/
using namespace std;
typedef long long ll;
#define N 1005
#define M 5005
struct Edge{
    int v,next;
}e[M<<1];
int ne,head[N];
void add_edge(int u,int v){
    e[ne].v=v,e[ne].next=head[u],head[u]=ne++;
}
int colr[N];
bool color(int u){
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].v;
        if(colr[u] == colr[v]) return false;
        if(!colr[v]){
            colr[v] = (colr[u] == 1 ? 2 : 1);
            if(!color(v)) return false;
        }
    }
    return true;
}
bool isBigraph(int n){
    memset(colr,0,sizeof(colr));
    for(int i = 1;i <= n;i++){
        if(!colr[i]){
            colr[i] = 1;
            if(!color(i)) return false;
        }
    }
    return true;
}
int match[N],vis[N];
bool findCrossPath(int u){
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].v;
        if(!vis[v]){
            vis[v] = 1;
            if(match[v] == -1 || findCrossPath(match[v])){
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
    }
    return false;
}
int maxMatch(int n){
    int ret = 0;
    memset(match,-1,sizeof(match));
    for(int i = 1;i <= n;i++){
        memset(vis,0,sizeof(vis));
        if(colr[i] == 1 && findCrossPath(i)) ret++;
    }
    return ret;
}
int main(){
    int n,m,u,v;
    while(~scanf("%d %d",&n,&m)){
        ne = 0;
        memset(head,-1,sizeof(head));
        for(int i = 0;i < m;i++){
            scanf("%d %d",&u,&v);
            add_edge(u,v),add_edge(v,u);
        }
        isBigraph(n);
        int ans = maxMatch(n);
        for(int i = 1;i <= n;i++){
            printf("%d: match:%d, colr:%d \n", i,match[i],colr[i]);
        }
        printf("%d\n%d\n", ans,n-ans);
    }
    return 0;
}