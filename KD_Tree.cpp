/*
Template:K-Dtree
Author:lxyxynt
Lang:C++
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;
typedef long long ll;
 
const int inf = 1000000000;
const int maxn = 100000+10;
const ll ll_inf = 1ll<<60;
const int maxD = 6;
const int maxK = 20;
int m;
struct point{
    int x[maxD];
    point(){}
    void read(){
        for (int i=0;i<m;++i) 
            scanf("%d",&x[i]);
    }
};
vector<point> a;
int t[maxn][maxD];
int divX[maxn];
int n,now,K;
 
bool cmp(point a, point b) {
    return a.x[now] < b.x[now];
}
 
void buildTree(int left, int right, point a[]) {
    if (left >= right) return;
    int mid = (left + right) >> 1;
    int minx[maxD],maxx[maxD];
    for (int i=0;i<m;++i){ 
        minx[i]=inf;
        maxx[i]=-inf;
    }
    for (int i = left; i < right; i++)
        for (int j=0;j<m;++j){
            minx[j]=min(minx[j],a[i].x[j]);
            maxx[j]=max(maxx[j],a[i].x[j]);
        }
    now=0;
    for (int i=1;i<m;++i)
        if (maxx[i]-minx[i]>maxx[now]-minx[now]) now=i;
    divX[mid]=now;
    nth_element(a + left, a + mid, a + right, cmp);
 
    for (int i=0;i<m;++i) t[mid][i]=a[mid].x[i];
     
    if (left + 1 == right) return;
    buildTree(left, mid, a);
    buildTree(mid + 1, right, a);
}
 
long long closestDist[maxK];
int closestNode[maxK][maxD];
 
void update(ll d,int pt[]){
    for (int i=1;i<=K;++i)
        if (closestDist[i]>d){
            for (int j=K;j>i;--j){
                closestDist[j]=closestDist[j-1];
                for (int k=0;k<m;++k) 
                    closestNode[j][k]=closestNode[j-1][k];
            }
            closestDist[i]=d;
            for (int k=0;k<m;++k) 
                closestNode[i][k]=pt[k];
            return;
        }
}       
 
void findD(int left, int right,const point& p) {
    if (left >= right) return;
    int mid = (left + right) >> 1;
    ll dx[maxD];
    ll d=0;
    for (int i=0;i<m;++i){
       dx[i]=p.x[i]-t[mid][i];
       d+=dx[i]*dx[i];
    }
    //注意能否查自己,d(距离)能否等于0
    update(d,t[mid]);
     
    if (left + 1 == right) return;
    ll delta = dx[divX[mid]];
    ll delta2 = delta*delta;
    int l1=left,r1=mid;
    int l2=mid+1,r2=right;
    if (delta>0){
        swap(l1,l2);
        swap(r1,r2);
    }
    findD(l1, r1, p);
    if (delta2 < closestDist[K])
        findD(l2, r2, p);
}
 
void findNearestNeighbour(int n, const point& p) {
    for (int i=1;i<=K;++i) 
        closestDist[i] = ll_inf;
    findD(0, n, p);
}
 
void print(){
    printf("the closest %d points are:\n",K);
    for (int i=1;i<=K;++i){
        for (int j=0;j<m-1;++j)
            printf("%d ",closestNode[i][j]);
        printf("%d\n",closestNode[i][m-1]);
    }
}
 
int main(){
    while (scanf("%d%d",&n,&m)==2){
        a.clear();
        point P;
        for (int i=0;i<n;++i){ 
            P.read();
            a.push_back(P);
        }
        vector<point> b(a);
        buildTree(0,n,&b[0]);
         
        int q;
        scanf("%d",&q);
        while (q--){
            P.read();
            scanf("%d",&K);
            findNearestNeighbour(n,P);
            print();
        }
    }
    return 0;
}