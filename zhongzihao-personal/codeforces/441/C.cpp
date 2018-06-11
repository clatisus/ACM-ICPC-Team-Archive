#include<bits/stdc++.h>

const int N = 100010;

int cap[N];
std::vector <int> vec[N];

bool cmp(int x, int y){
	if (cap[x] != cap[y]) return cap[x] > cap[y];
	return x < y;
}

bool cmp(std::vector <int> &vec1, std::vector <int> &vec2){
	int sz1 = vec1.size(), sz2 = vec2.size();
	for (int i = 0; i < sz1 && i < sz2; ++ i){
		if (vec1[i] != vec2[i]){
			return cmp(vec1[i], vec2[i]);
		}
	}
	return sz1 <= sz2;
}

void solve(int sit, int l, int r){
	if (l == r) return;
	int ssit = -1;
	int max = -1;
	for (int i = l; i <= r; ++ i){
		if (vec[i].size() <= sit){
			max = i;
			continue;
		}
	}
	for (int i = l; i <= max; ++ i){
		if (vec[i].size() > sit){
			printf("No\n");
			exit(0);
		}
	}
	l = std::max(l, max + 1);
	if (l == r){
		return;
	}
	for (int i = l; i < r; ++ i){
		if (vec[i][sit] > vec[i + 1][sit]){
			if (~ssit){
				printf("No\n");
				exit(0);
			}
			ssit = i;
		}
	}
	for (int i = l; i <= ssit; ++ i){
		cap[vec[i][sit]] = 1;
	}
	int pre = l;
	for (int i = l + 1; i <= r + 1; ++ i){
		if (i > r || vec[i][sit] != vec[i - 1][sit]){
			solve(sit + 1, pre, i - 1);
			pre = i;
		}
	}
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	int INF = m + 1;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		for (int j = 0, y; j < x; ++ j){
			scanf("%d", &y);
			vec[i].push_back(y);
		}
	}
	solve(0, 0, n - 1);
	bool flag = true;
	for (int i = 0; i < n - 1; ++ i){
		if (!cmp(vec[i], vec[i + 1])){
			flag = false;
			break;
		}
	}
	if (!flag){
		return printf("No\n"), 0;
	}
	int cnt = 0;
	for (int i = 1; i <= m; ++ i){
		cnt += cap[i];
	}
	printf("Yes\n%d\n", cnt);
	for (int i = 1; i <= m; ++ i){
		if (cap[i]){
			printf("%d ", i);
		}	
	}
	putchar('\n');
	return 0;
}
