#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int MAX = 26; 
typedef struct TrieNode
{
	bool isStr;
	int num;
	struct TrieNode *next[MAX];
}Trie;
void insert(Trie *rt, string s){
	if(rt == NULL) return;
	Trie *p = rt;
	for(int i = 0;i < s.length();i++){
		if(p->next[s[i]-'a'] == NULL){
			Trie *tmp = (Trie *)malloc(sizeof(Trie));
			for(int j = 0;j < MAX;j++)
				tmp->next[j] = NULL;
			tmp->isStr = false;
			tmp->num = 0;
			p->next[s[i]-'a'] = tmp; 
		}
		p = p->next[s[i]-'a'];
		p->num++;
	}
	p->isStr = true; 
}
int search(Trie *rt, string s){
	if(rt == NULL) return 0;
	Trie *p = rt;
	for(int i = 0;i < s.length() && p != NULL;i++)
		p = p->next[s[i]-'a'];
	if(p != NULL) return p->num; //用于计算字典中具有公共前缀s的个数
	//return p != NULL && p->isStr; //用于判断s是否存在字典中
	return 0;
}
void del(Trie *rt){
	if(rt == NULL) return;
	for(int i = 0;i < MAX;i++)
		if(rt->next[i] != NULL) del(rt->next[i]);
	free(rt);
}
int main(){
		string s;
		Trie *rt = (Trie *)malloc(sizeof(Trie));
		rt->isStr = false;
		rt->num = 0;
		for(int i = 0;i < MAX;i++)
			rt->next[i] = NULL;
		int i = 0;
		while(getline(cin,s) && s.length() != 0){
			insert(rt,s);
		}
		while(cin >> s){
			cout << search(rt,s) << endl;
		}
		del(rt);
		return 0;
}