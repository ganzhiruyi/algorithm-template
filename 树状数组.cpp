#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
/*求逆序数*/
using namespace std;
typedef long long ll;
const int N = 500010;
int C[N],n,ref[N];
struct Node{
	int val,id;
}A[N];
bool cmp(Node a,Node b){
	return a.val < b.val;
}
int lowbit(int x){
	return x & (-x);
}
int getSum(int x){
	int ret = 0;
	while(x){
		ret += C[x];
		x -= lowbit(x);
	}
	return ret;
}
void update(int x,int num){
	while(x <= n){
		C[x] += num;
		x += lowbit(x);
	}
}
int main(){
	while(scanf("%d",&n) && n){
		for(int i = 1;i <= n;i++){
			scanf("%d",&A[i].val);
			A[i].id = i;
		}
		//离散化A数组到ref数组
		sort(A+1,A+1+n,cmp);
		for(int i = 1;i <= n;i++)
			ref[A[i].id] = i;
		ll ans = 0; 
		memset(C,0,sizeof(C));
		for(int i = 1;i <= n;i++){
			update(ref[i],1);
			ans += i - getSum(ref[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}