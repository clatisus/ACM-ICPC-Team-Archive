#include<bits/stdc++.h>

const int N = 100010;

int n;
int a[N];
bool vis[N];

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
	}
	int now = 1, cnt = 1;
	for ( ; ; ++ cnt){
		vis[now] = true;
		now = a[now];
		if (now == 2){
			return printf("%d\n", cnt), 0;
		}
		if (vis[now]){
			break;
		}
	}
	return printf("-1\n"), 0;
}
