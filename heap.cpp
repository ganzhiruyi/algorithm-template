#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int MAX = 100005;
#define ls (rt<<1)
#define rs (rt<<1|1)
template <class T>
class Max_Heap{
	int heap_cnt;
	T A[MAX*4];
	void heapify(int rt){
		int largest = 0;
		if(ls <= heap_cnt) largest = A[ls] <= A[rt] ? rt : ls;
		if(rs <= heap_cnt) largest = A[rs] <= A[largest] ? largest : rs;
		if(largest && largest != rt){
			swap(A[rt],A[largest]);
			heapify(largest);
		}
	}
public:
	void init_heap(){
		heap_cnt = 0;
	}
	void insert_heap(T val){
		int idx = ++heap_cnt;
		int fa = idx>>1;
		while(idx > 1 && val > A[fa]){
			A[idx] = A[fa];
			idx = fa;
			fa = idx>>1;
		}
		A[idx] = val;

	}
	T extract_max_heap(){
		T ret = A[1];
		swap(A[heap_cnt],A[1]);
		heap_cnt--;
		heapify(1);
		return ret;
	}
};
int main(){
	int m,w;
	string op;
	while(cin >> m){
		Max_Heap<int> h;
		h.init_heap();
		for(int i = 0;i < m;i++){
			cin >> op;
			if(op[0] == 'A'){
				cin >> w;
				h.insert_heap(w);
			} 
			else cout << h.extract_max_heap() << endl;
		}
	}
	return 0;
}