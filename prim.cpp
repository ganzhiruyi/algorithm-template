#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int N = 100005;
const int M = 1000005;
const int inf = (1<<30);
#define ls (rt<<1)
#define rs (rt<<1|1)
struct Edge{
	int next,v,w;
}e[M<<1];
int ne,head[N];
bool mstSet[N];
void add_edge(int u,int v,int w){
	e[ne].v = v,e[ne].w = w,e[ne].next = head[u];
	head[u] = ne++;
}
class HeapNode{
public:
	int edgeId,w;
	HeapNode(){}
	HeapNode(int a,int c):edgeId(a),w(c){}
	bool operator < (HeapNode a){
		return w <= a.w;
	}
};
class MinHeap{
public:
	int cnt_heap;
	HeapNode A[M<<2];
	MinHeap(){
		cnt_heap = 0;
	}
	void heapify(int rt){
		int largest = -1;
		if(ls <= cnt_heap) largest = A[rt] < A[ls] ? rt : ls;
		if(rs <= cnt_heap) largest = A[largest] < A[rs] ? largest : rs;
		if(largest != -1 && largest != rt){
			swap(A[largest],A[rt]);
			heapify(largest);	
		} 
	}
	void insert(int edgeId){
		HeapNode tmp = HeapNode(edgeId,e[edgeId].w);
		int idx = ++cnt_heap;
		int fa = idx>>1;
		while(idx > 1 && tmp < A[fa]){
			A[idx] = A[fa];
			idx = fa;
			fa = idx>>1;
		}
		A[idx] = tmp;
	}
	HeapNode extract_min(){
		HeapNode ret = A[1];
		swap(A[1],A[cnt_heap]);
		cnt_heap--;
		if(cnt_heap) heapify(1);
		return ret;
	}
};
int prim(int n){
	int ret = 0,cnt_mstSet = 1;
	memset(mstSet,false,sizeof(mstSet));
	mstSet[1] = true;
	MinHeap h = MinHeap();
	for(int i = head[1];i != -1;i = e[i].next) h.insert(i);
	while(cnt_mstSet < n){
		HeapNode t = h.extract_min();
		int v = e[t.edgeId].v;
		while(mstSet[v]){
			t = h.extract_min();
			v = e[t.edgeId].v;
		}
		mstSet[v] = true;
		ret += t.w;
		cnt_mstSet++;
		for(int i = head[v];i!= -1;i = e[i].next) h.insert(i);
	}
	return ret;
}
int main(){
	int n,m,u,v,w;
	while(cin >> n >> m){
		ne = 0;
		memset(head,-1,sizeof(head));
		for(int i = 0;i < m;i++){
			cin >> u >> v >> w;
			add_edge(u,v,w),add_edge(v,u,w);
		}
		cout << prim(n) << endl;
	}
	return 0;
}