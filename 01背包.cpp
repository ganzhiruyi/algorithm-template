#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
using namespace std;
const int N = 505;
const int M = 100005;
//int dp[N][M];
int main(){
	int n,m,cost[N],val[N],f[M];
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
		cin >> cost[i] >> val[i];
	/*复杂版本
	memset(dp,0,sizeof(dp));
	for(int i = 1;i <= n;i++)
		for(int j = 0;j <= m;j++)
			if(j >= cost[i])
				dp[i][j] = max(dp[i-1][j],dp[i-1][j-cost[i]]+val[i]);
			else
				dp[i][j] = dp[i-1][j];
	int ans = dp[n][m];
	*/
	//压缩版本
	memset(f,0,sizeof(f));
	for(int i = 1;i <= n;i++)
		for(int j = m;j >= cost[i];j--)
			f[j] = max(f[j],f[j-cost[i]]+val[i]);
	cout << f[m] << endl;
	return 0;
}