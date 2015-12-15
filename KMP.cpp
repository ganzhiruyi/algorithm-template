#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const int N = 10010;
void get_next(char *t, int *next){
	int j,n = strlen(t);
	next[0] = -1;
	for(int i = 1;i < n;i++){
		j = next[i-1];
		while(j >= 0 && t[j+1] != t[i]) j = next[j];
		if(t[j+1] == t[i]) next[i] = j+1;
		else next[i] = -1;
	}
}
//返回的是s中包含t的个数
int kmp(char *s, char *t){
	int i = 0,j = 0,n = strlen(s),m = strlen(t),ret = 0;
	int *next = new int[m];
	get_next(t,next);
	while(i < n && j < m){
		if(s[i] == t[j]){
			i++;
			j++;
			if(j == m){
				ret++;
				j = next[j-1] + 1;
			}
		}
		else if(j == 0) i++;
		else j = next[j-1] + 1;
	}
	delete[] next;
	return ret;
}
int main(){
	int n;
	scanf("%d",&n);
	char S[N],T[N];
	while(n--){
		scanf("%s",T);
		scanf("%s",S);
		printf("%d\n", kmp(S,T));
	}
	return 0;
}