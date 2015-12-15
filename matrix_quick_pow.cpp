#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const int N = 2;
const int MOD = 10000;
int n;
struct Mat{
	int mat[N][N];
};
Mat operator * (Mat a,Mat b){
	Mat ret;
	memset(ret.mat,0,sizeof(ret.mat));
	for(int i = 0;i < N;i++){
		for(int k = 0;k < N;k++){
			if(!a.mat[i][k]) continue;
			for(int j = 0;j < N;j++){
				if(!b.mat[k][j]) continue;
				ret.mat[i][j] += a.mat[i][k]*b.mat[k][j];
				if(ret.mat[i][j] >= MOD) ret.mat[i][j] %= MOD;
			}
		}
	}
	return ret;
}
Mat operator ^ (Mat a,int b){
	Mat c;
	for(int i = 0;i < N;i++)
		for(int j = 0;j < N;j++) c.mat[i][j] = i == j;
	while(b){
		if(b&1) c = c*a;
		a = a*a;
		b >>= 1;
	}
	return c;
}
int main(){
	while(scanf("%d",&n) && n != -1){
		Mat c;
		c.mat[0][0] = 1,c.mat[0][1] = 1,c.mat[1][0] = 1,c.mat[1][1] = 0;
		Mat ans = c^n;
		printf("%d\n", ans.mat[0][1]%MOD);
	}
	return 0;
}
