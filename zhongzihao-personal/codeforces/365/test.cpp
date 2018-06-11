#include<bits/stdc++.h>
#define MAXN (100010)

struct node{
	int x;
	int id;
}f[MAXN];

int e[MAXN];

bool cmp(const node &a, const node &b){
	if (a.x < b.x) return true;
	if (a.x == b.x) return a.id < b.id;
	return false;
}

int main(){
	int n = 100000;
	for(int i = 1; i <= n; ++ i){
		if(i % 2) f[i].x = 1;
		else f[i].x = 0;
		f[i].id = i;
	}
	std::sort(f + 1, f + n + 1, cmp);
	for(int i = 1; i <= n; ++ i){
		e[f[i].id] = i;
	}//ÀëÉ¢»¯
	return 0;
}
