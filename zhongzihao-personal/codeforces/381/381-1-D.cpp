#include<bits/stdc++.h>

const int N = 310;

std::map <int, std::vector <int>> Hash[N];
std::set <int> set;
char s[N];
int n, ans[N];

int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%s", s);
		int p = -1, c = -1;
		if (s[0] != '?'){
			int len = strlen(s);
			p = 0;
			for (int j = 0; j < len; ++ j){
				p = p * 10 + s[j] - '0';
			}
		}
		scanf("%s", s);
		if (s[0] != '?'){
			int len = strlen(s);
			c = 0;
			for (int j = 0; j < len; ++ j){
				c = c * 10 + s[j] - '0';
			}
		}
		if (p != -1){
			Hash[c][p].push_back(i);
		}
		else{
			set.insert(i);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++ i){
		if (!Hash[i].size()){
			continue;
		}
		while (!Hash[i][0].size() || Hash[i][0].size() % i){
			Hash[i][0].push_back(0);
		}
		auto u = Hash[i].end();
		-- u;
		for (int j = 1; j < u -> first; ++ j){
			if (!Hash[i].count(j)){
				Hash[i][j].push_back(0);
			}
		}
		for (u = Hash[i].begin(); u != Hash[i].end(); ++ u){
			cnt += u -> second.size();
		}
	}
	if (cnt > n){
		return printf("-1\n"), 0;
	}
	for (int i = 1; i <= n; ++ i){
		if (!Hash[i].size()){
			continue;
		}
		auto &v = Hash[i][0];
		for (int j = 0; j < v.size(); ++ j){
			if (!v[j]){
				v[j] = *(set.begin());
				set.erase(set.begin());
			}
		}
		for (int j = 0; j < v.size(); ++ j){
			if ((j + 1) % i){
				ans[v[j]] = v[j + 1];
			}
			else{
				ans[v[j]] = v[j + 1- i];
			}
		}
		int k = 1;
		while (Hash[i].count(k)){
			auto &v = Hash[i][k];
			for (int j = 0; j < v.size(); ++ j){
				if (!v[j]){
					v[j] = *(set.begin());
					set.erase(set.begin());
				}
				ans[v[j]] = Hash[i][k - 1][0];
			}
			++ k;
		}
	}
	for (auto u = set.begin(); u != set.end(); ++ u){
		ans[*u] = *u;	
	}
	for (int i = 1; i <= n; ++ i){
		printf("%d ", ans[i]);
	}
	return printf("\n"), 0;
}
