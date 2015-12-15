#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define N 105
int G[N][N],in[N],vis[N],DFN[N],LOW[N],Stack[N],fa[N],NG[N][N];
int n,top,timeStap,cntSCC;
void tarjan(int u){
    //tarjan求强连通分量
    vis[u] = in[u] = 1;
    Stack[top++] = u;
    DFN[u] = LOW[u] = ++timeStap;
    for(int v = 1;v <= n;v++){
        if(!G[u][v]) continue;
        if(!vis[v]){
            tarjan(v);
            LOW[u] = min(LOW[u],LOW[v]);
        }
        else if(in[v]){
            LOW[u] = min(DFN[v],LOW[u]);
        }
    }
    if(DFN[u]==LOW[u]){
        ++cntSCC;
        int v = Stack[--top];
        in[v] = 0;
        fa[v] = cntSCC;
        while(u != v){
            v = Stack[--top];
            in[v] = 0;
            fa[v] = cntSCC;
        }
    }
}
int inDegree[N],outDegree[N];
void buildNewGraph(){
    //缩点构建新图
    memset(NG,0,sizeof(NG));
    memset(inDegree,0,sizeof(inDegree));
    memset(outDegree,0,sizeof(outDegree));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(i==j || !G[i][j] || fa[i]==fa[j]) continue;
            if(!NG[fa[i]][fa[j]]){
                NG[fa[i]][fa[j]] = 1;
                inDegree[fa[j]]++,outDegree[fa[i]]++;
            }
        }
    }
}
int main(){
    int u,v;
    while(~scanf("%d",&n)){
        memset(G,0,sizeof(G));
        for(int i = 1;i <= n;i++){
            while(~scanf("%d",&v) && v){
                G[i][v] = 1;
            }
        }
        memset(vis,0,sizeof(vis));
        memset(in,0,sizeof(in));
        cntSCC = timeStap = top = 0;
        for(int i = 1;i <= n;i++)
            if(!vis[i]) tarjan(i);
        buildNewGraph();
        int ans1 = 0,ans2 = 0;
        for(int i = 1;i <= cntSCC;i++){
            if(!inDegree[i]) ans1++;
            if(!outDegree[i]) ans2++;
        }
        if(cntSCC == 1) ans2 = 0;//只有一个强连通分量，这时不需要加边
        else ans2 = max(ans1,ans2); 
        printf("%d\n%d\n", ans1,ans2);
    }
    return 0;
}