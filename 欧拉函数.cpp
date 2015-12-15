#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define N 100005
#define MAXV 100000000
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
int phi[MAXV+5],prime[MAXV];
bool is_prime[MAXV];
void get_phi(){
    phi[1] = 1;
    int primeCnt = 0;
    memset(is_prime,true,sizeof(is_prime));
    for(int i = 2;i < MAXV;i++){ // 枚举第一个因子
        if(is_prime[i]){
            prime[primeCnt++] = i;
            phi[i] = i-1;
        }
        for(int j = 0;j<primeCnt && i*prime[j] < MAXV;j++){ 
            is_prime[i*prime[j]] = false; 
            if(i%prime[j] == 0){
                phi[i*prime[j]] = phi[i]*prime[j];
                break; // 每次只筛掉最小的素数
            }
            else{
                phi[i*prime[j]] = phi[i]*(prime[j]-1);
            }
        }
    }
}
int phi(int n){
    int ret = 1;
    for(int i = 2;i*i <= n;i++){
        if(n % i == 0){
            n /= i;
            ret *= (i-1);
            while(n % i == 0){
                n /= i;
                ret *= i;
            }
        }
    }
    if(n > 1) ret *= (n-1); // 这里是避免n就是素数，for没起作用
    return ret;
}
int main(){
    int n;
    while(~scanf("%d",&n) && n){
        printf("%d\n", n-phi(n)-1);
    }
    return 0;
}