#include<bits/stdc++.h>

const int N = 510;
typedef std::pair <int, int> pii;

int x[N], a[N * N];
pii p[N];

void no(){
	puts("No");
	exit(0);
}

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &x[i]);
		a[x[i]] = i;
		p[i] = {x[i], i};
	}
	std::sort(p + 1, p + n + 1);
	std::set <int> set;
	for (int i = 1; i <= n * n; ++ i){
		if (!a[i]) set.insert(i);
	}
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j < p[i].second; ++ j){
			int sit = *(set.begin());
			if (sit > p[i].first) no();
			a[sit] = p[i].second;
			set.erase(sit);
		}
	}
	for (int i = n; i >= 1; -- i){
		for (int j = p[i].second + 1; j <= n; ++ j){
			int sit = *(-- set.end());
			if (sit < p[i].first) no();
			a[sit] = p[i].second;
			set.erase(sit);
		}
	}
	puts("Yes");
	for (int i = 1; i <= n * n; ++ i){
		printf("%d%c", a[i], " \n"[i == n * n]);
	}
	return 0;
}
