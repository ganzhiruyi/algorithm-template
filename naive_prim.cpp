#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 1005;
const int inf = 0x7fffffff;
int G[N][N],dis[N],fa[N];//dis[u]表示顶点u到当前最小生成树的距离
bool mstSet[N];//mstSet[u]表示顶点u是否已经加入到当前的最小生成树中
int min_dis_idx(int n){
	int min_val = inf,min_idx = 0;
	for(int i = 0;i < n;i++){
		if(!mstSet[i] && dis[i] < min_val){
			min_val = dis[i];
			min_idx = i;
		}
	}
	return min_idx;
}
int prim_MST(int rt,int n){
	int res = 0,cnt_vex = 1;
	for(int i = 0;i < n;i++) mstSet[i] = false,dis[i] = inf;
	mstSet[rt] = true;
	dis[rt] = 0;
	fa[rt] = -1;
	while(cnt_vex < n){
		int u = min_dis_idx(n);
		mstSet[u] = true;
		for(int v = 0;v < n;v++){
			if(G[u][v] && !mstSet[v] && G[u][v] < dis[v]){
				fa[v] = u,dis[v] = G[u][v];
			}	
		}
		cnt_vex++;
	}
	for(int v = 1;v < n;v++){
		res += G[fa[v]][v];
	}
	return res;
}
int main(){
	int n;
	while(~scanf("%d",&n)){
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++) scanf("%d",&G[i][j]);
		printf("%d\n", prim_MST(0,n));
	}
	return 0;
}