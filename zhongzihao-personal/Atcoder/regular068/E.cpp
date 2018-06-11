#include<bits/stdc++.h> 
#define lowbit(x) ((x) & (-(x)))

const int N = 300010;

int n, m, c[N], ans[N];

void add(int l, int r){
	++ r;
	while (r < N){
		-- c[r];
		r += lowbit(r);
	}
	while (l < N){
		++ c[l];
		l += lowbit(l);
	}
}

int query(int sit){
	int ret = 0;
	while (sit){
		ret += c[sit];
		sit -= lowbit(sit);
	}
	return ret;
}

std::vector <std::pair <int, std::pair <int, int>>> vec;

int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0, l, r; i < n; ++ i){
		scanf("%d%d", &l, &r);
		vec.push_back({r - l + 1, {l, r}});
	}
	sort(vec.begin(), vec.end());
	for (int i = 1, sit = 0; i <= m; ++ i){
		while (vec[sit].first <= i && sit < n){
			add(vec[sit].second.first, vec[sit].second.second);
			++ sit;
		}
		for (int j = 1; i * j <= m; ++ j){
			ans[i] += query(i * j);
		}
		ans[i] += n - sit;
	}
	for (int i = 1; i <= m; ++ i){
		printf("%d\n", ans[i]);
	}
	return 0;
}
