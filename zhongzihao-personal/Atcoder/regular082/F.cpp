#include<bits/stdc++.h>

const int N = 100010;
typedef std::pair <int, int> pii;

int x, k, q;
int r[N], ans[N];
std::pair <pii, int> query[N];

int main(){
	scanf("%d%d", &x, &k);
	for (int i = 0; i < k; ++ i){
		scanf("%d", &r[i]);
	}
	scanf("%d", &q);
	for (int i = 0, t, a; i < q; ++ i){
		scanf("%d%d", &t, &a);
		query[i] = {{t, a}, i};
	}
	std::sort(query, query + q);
	pii one = {0, 0}, two = {x, x};
	for (int i = 0, j = 0; i < q; ++ i){
		while (j < k && query[i].first.first >= r[j]){
			int dif = r[j] - (j ? r[j - 1] : 0);
			if (j & 1){
				if (two.second + dif <= x){
					one.second += dif;
					two.second += dif;
				}
				else if (one.second + dif < x){
					one.second += dif;
					two = {two.first - dif + x - two.second, x};
				}
				else{
					one = {0, x};
					two = {0, x};
				}
			}
			else{
				if (one.second >= dif){
					one.second -= dif;
					two.second -= dif;
				}
				else if (two.second > dif){
					one = {one.first + dif - one.second, 0};
					two.second -= dif;
				}
				else{
					one = {0, 0};
					two = {0, 0};
				}
			}
			++ j;
		}
		if (query[i].first.second <= one.first){
			ans[query[i].second] = one.second;
		}
		else if (query[i].first.second >= two.first){
			ans[query[i].second] = two.second;
		}
		else{
			ans[query[i].second] = one.second + query[i].first.second - one.first;
		}
		int xx = j ? r[j - 1] : 0;
		ans[query[i].second] += j & 1 ? query[i].first.first - xx : xx - query[i].first.first;
		if (ans[query[i].second] < 0){
			ans[query[i].second] = 0;
		}
		if (ans[query[i].second] > x){
			ans[query[i].second] = x;
		}
	}
	for (int i = 0; i < q; ++ i){
		printf("%d\n", ans[i]);
	}
	return 0;
}
