#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 105;
const int inf = 0x7fffffff;
int n,m,dis[N][N];
void floyed(){
	for(int k = 1;k <= n;k++)
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++){
				if(i == j || i == k || j == k) continue;
				if(dis[i][k] < inf && dis[k][j] < inf)
					dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
			}
}
int main(){
	while(~scanf("%d %d",&n,&m)){
		for(int i = 0;i <= n;i++)
			for(int j = 0;j <= n;j++) dis[i][j] = i == j ? 0 : inf;
		int u,v,w;
		for(int i = 0;i < m;i++){
			scanf("%d %d %d",&u,&v,&w);
			dis[u][v] = dis[v][u] = min(dis[u][v],w); //因为u、v之间可能有多条边相连
		}
		floyed();
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++) printf("%d ", dis[i][j]); 
			printf("\n");
		}
	}
	return 0;
}