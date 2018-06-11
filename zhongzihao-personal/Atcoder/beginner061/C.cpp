#include<bits/stdc++.h>

const int N = 100010;

int n;
long long k;
std::pair <int, int> p[N];

int main(){
	scanf("%d%lld", &n, &k);
	for (int i = 0; i < n; ++ i){
		scanf("%d%d", &p[i].first, &p[i].second);
	}
	std::sort(p, p + n);
	for (int i = 0; i < n; ++ i){
		k -= p[i].second;
		if (k <= 0){
			return printf("%d\n", p[i].first), 0;
		}
	}
}
