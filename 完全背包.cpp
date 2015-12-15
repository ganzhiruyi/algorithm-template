#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;
const int N = 510;
const int M = 100010;
int main(){
	int n,m,cost[N],val[N],f[M];
	while(cin >> n >> m){
		for(int i = 1;i <= n;i++)
			cin >> cost[i] >> val[i];
		memset(f,0,sizeof(f));
		for(int i = 1;i <= n;i++){
			for(int j = cost[i];j <= m;j++)
				f[j] = max(f[j],f[j-cost[i]]+val[i]);
		}
		cout << f[m] << endl;
	}
	return 0;
}