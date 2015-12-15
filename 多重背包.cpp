#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100005
#define M 10005
int n,m;
int num[N],v[N],w[N];
int f[M];
struct Node{
	int v,w;
	bool operator < (const Node &a)const{
		if(v == a.v) return w < a.w;
		return v < a.v;
	}
	bool operator == (const Node &a)const{
		return v == a.v && w == a.w;
	}
}node[N];
void zero_one_pack(int v,int w){
	for(int i = m;i >= w;i--) f[i] = max(f[i],f[i-w]+v);
}
void completePack(int v,int w){
	for(int i = w;i <= m;i++) f[i] = max(f[i],f[i-w]+v);
}
void multiplePack(int v,int w,int amount){
	if(w*amount > m){
		completePack(v,w);
		return;
	}
	int k = 1;
	while(k < amount){
		zero_one_pack(k*v,k*w);
		amount -= k;
		k <<= 1;
	}
	zero_one_pack(amount*v,amount*w);
}
int main(){
	char s[15];
	while(~scanf("%d %d",&n,&m)){
		for(int i = 0;i < n;i++)
			scanf("%s %d %d",s,&node[i].v,&node[i].w);
		sort(node,node+n);
		memset(num,0,sizeof(num));
		int tn = n;
		n = 1;
		num[n] = 1,v[n] = node[0].v,w[n] = node[0].w;
		for(int i = 1;i < tn;i++){
			if(node[i] == node[i-1]) num[n]++;
			else{
				num[++n] = 1;
				v[n] = node[i].v,w[n] = node[i].w;
			}
		}
		memset(f,0,sizeof(f));
		for(int i = 1;i <= n;i++)
			multiplePack(v[i],w[i],num[i]);
		printf("%d\n", f[m]);
	}
	return 0;
}