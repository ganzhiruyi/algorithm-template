#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1005;
const int MAXC = 26;
char g[N][N];
int dir[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int n,m;
struct Ans{
	int x,y,d;
}ans[N];
struct Trie{
	int id;
	Trie *next[MAXC],*fail;
	Trie(){
		memset(next,NULL,sizeof(next));
		fail = NULL;
		id = -1;
	}
};
void insert(Trie *rt,char *str,int id){
	Trie *p = rt;
	while(*str){
		int idx = *str - 'A';
		if(!p->next[idx]) p->next[idx] = new Trie();
		p = p->next[idx];
		str++;
	}
	p->id = id;
}
void del(Trie *rt){
	if(rt == NULL) return;
	for(int i = 0;i < MAXC;i++)
		if(rt->next[i]) del(rt->next[i]);
	delete rt;
}
queue<Trie*> q;
void build_DFA(Trie *rt){
	while(!q.empty()) q.pop();
	q.push(rt);
	while(!q.empty()){
		Trie *p = q.front();
		q.pop();
		for(int i = 0;i < MAXC;i++){
			if(!p->next[i]) continue;
			if(p == rt) p->next[i]->fail = rt;
			else{
				Trie *f = p->fail;
				while(f){
					if(f->next[i]){
						p->next[i]->fail = f->next[i];
						break;
					}
					f = f->fail;
				}
				if(!f) p->next[i]->fail = rt;
			}
			q.push(p->next[i]);
		}
	}
}
int run_DFA(Trie *rt,int x,int y,int d){
	Trie *p = rt;
	int idx,tx,ty,step = 0,res = 0;
	while(1){
		tx = x+step*dir[d][0],ty = y+step*dir[d][1];
		if(0 > tx || tx >= n || 0 > ty || ty >= m) break;
		idx = g[tx][ty]-'A';
		while(!p->next[idx] && p != rt) p = p->fail;
		p = p->next[idx];
		if(!p) p = rt;
		Trie *tmp = p;
		while(tmp && tmp->id != -1){
			if(ans[tmp->id].d == -1){
				//保存的是模式串的最后一个字符的坐标
				ans[tmp->id].x=tx,ans[tmp->id].y=ty,ans[tmp->id].d=d;
				res++;
			}
			tmp = tmp->fail; 
		}
		step++; 
	}
	return res;
}
int main(){
	int k,cnt = 0;
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 0;i < n;i++) scanf("%s",g[i]);
	Trie *rt = new Trie();
	char line[N];
	int len[N];
	for(int i = 0;i < k;i++){
		scanf("%s",line);
		len[i] = strlen(line);
		insert(rt,line,i);
	}
	memset(ans,-1,sizeof(ans));
	build_DFA(rt);
	//遍历行(第一列、最后一列)
	for(int i = 0;i < n && cnt < k;i++){
		for(int j = 0;j < 8 && cnt < k;j++){
			cnt += run_DFA(rt,i,0,j);
			cnt += run_DFA(rt,i,m-1,j);
		}
	}
	//遍历列(第一行、最后一行)
	for(int i = 0;i < m && cnt < k;i++){
		for(int j = 0;j < 8 && cnt < k;j++){
			cnt += run_DFA(rt,0,i,j);
			cnt += run_DFA(rt,n-1,i,j);
		}
	}
	for(int i = 0;i < k;i++)
		printf("%d %d %c\n", ans[i].x-dir[ans[i].d][0]*(len[i]-1),
			ans[i].y-dir[ans[i].d][1]*(len[i]-1),ans[i].d+'A');
	return 0;
}