#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXK = 26;
const int MAX_TEXT_LEN = 1000010;
int ans;
char text[MAX_TEXT_LEN];
struct Trie{
    int cnt;
    Trie *next[MAXK], *fail;
    Trie(){
        memset(next,NULL,sizeof(next));
        cnt = 0;
        fail = NULL;
    }
};
void insert(Trie *rt,char *str){
    if(!rt) return;
    Trie *p = rt;
    int len = strlen(str);
    for(int i = 0;i < len;i++){
        int idx = str[i] - 'a';
        if(!p->next[idx])
            p->next[idx] = new Trie();
        p = p->next[idx];
    }
    p->cnt++;
}
void del(Trie *rt){
    if(!rt) return;
    Trie *p = rt;
    for(int i = 0;i < MAXK;i++)
        if(p->next[i]) del(p->next[i]);
    free(rt);
}
queue<Trie*> q;
void build_DFA(Trie *rt){
    while(!q.empty()) q.pop();
    q.push(rt);
    while(!q.empty()){
        Trie *cur = q.front();
        q.pop();
        for(int i = 0;i < MAXK;i++){
            if(!cur->next[i]) continue;
            if(cur == rt) cur->next[i]->fail = rt;
            else{
                Trie *f = cur->fail;
                while(f){
                    if(f->next[i]){
                        cur->next[i]->fail = f->next[i];
                        break;
                    }
                    f = f->fail;
                }
                if(!f) cur->next[i]->fail = rt;
            }
            q.push(cur->next[i]);
        }
    }
}
void run_DFA(Trie *rt,char *str){
    Trie *p = rt;
    int i = 0,len = strlen(str);
    while(i < len){
        int idx = str[i] - 'a';
        while(!p->next[idx] && p != rt)
            p = p->fail;
        p = p->next[idx];
        if(!p) p = rt;
        Trie *tmp = p; //总的单词数是q->cnt U f(q)->cnt
        while(tmp && tmp->cnt){
            ans += tmp->cnt;
            tmp->cnt = 0;
            tmp = tmp->fail;
        }
        i++;
    }
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        char str[52];
        Trie *rt = new Trie();
        for(int i = 0;i < n;i++){
            scanf("%s",str);
            insert(rt,str);
        }
        build_DFA(rt);
        scanf("%s",text);
        ans = 0;
        run_DFA(rt,text);
        printf("%d\n", ans);
        del(rt);
    }
    return 0;
}