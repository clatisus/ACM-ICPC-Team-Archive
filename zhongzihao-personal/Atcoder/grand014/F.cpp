#include<bits/stdc++.h>

const int N = 200010;

int a[N], p[N], f[N], ans[N];
int n;

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &a[i]);
		p[a[i]] = i;
	}
	for (int i = n; i; -- i){
		if (!ans[i + 1]){
			if (i == n || p[i] < p[i + 1]){
				continue;
			}
			ans[i] = 1;
			f[i] = i + 1;
			continue;
		}
		if (p[f[i + 1]] < p[i] && p[i] < p[i + 1] || p[i] < p[i + 1] && p[i + 1] < p[f[i + 1]] || p[i + 1] < p[f[i + 1]] && p[f[i + 1]] < p[i]){
			ans[i] = ans[i + 1];
			f[i] = f[i + 1];
		}
		else{
			ans[i] = ans[i + 1] + 1;
			f[i] = i + 1;
		}
	}
	return printf("%d\n", ans[1]), 0;
}
