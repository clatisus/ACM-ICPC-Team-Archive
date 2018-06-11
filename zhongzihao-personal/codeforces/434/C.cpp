#include<bits/stdc++.h>

const int N = 100010;
const int M = 10;

char s[N][M];
int type[N], state[N], len[N], num[N];
char aux[M];

int randint(int n){
	return (rand() << 15 | rand()) % n;
}

int main(){
	srand(time((unsigned) NULL));
	int n;
	scanf("%d", &n);
	int cnt = 0;
	for (int i = 0; i < n; ++ i){
		scanf("%s%d", s[i], &type[i]);
		len[i] = strlen(s[i]);
		cnt += type[i];
	}
	for (int i = 0; i < n; ++ i){
		bool flag = true;
		for (int j = 0; j < len[i]; ++ j){
			if (s[i][j] < '0' || s[i][j] > '9'){
				flag = false;
				break;
			}
		}
		num[i] = 0;
		if (flag && s[i][0] > '0'){
			for (int j = 0; j < len[i]; ++ j){
				num[i] = num[i] * 10 + s[i][j] - '0';
			}
		}
		if (type[i]){
			if (1 <= num[i] && num[i] <= cnt){
				state[i] = 1;
			}
			else if (num[i] > cnt && num[i] <= n){
				state[i] = 2;
			}
		}
		else{
			if (1 <= num[i] && num[i] <= cnt){
				state[i] = 2;
			}
			else if (num[i] > cnt && num[i] <= n){
				state[i] = 1;
			}
		}
	}
	for (int i = 0; i < 6; ++ i){
		aux[i] = randint(26) + 'a';
	}
	std::vector <int> vec1, vec2;
	for (int i = 0; i < n; ++ i){
		if (state[i] == 2){
			if (type[i]){
				vec1.push_back(i);
			}
			else{
				vec2.push_back(i);
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++ i){
		ans += state[i] != 1;
	}
	ans += std::min(vec1.size(), vec2.size());
	printf("%d\n", ans);
	for (int i = 0, sz = std::min(vec1.size(), vec2.size()); i < sz; ++ i){
		printf("move %s %s\n", s[vec1[i]], aux);
		printf("move %s %s\n", s[vec2[i]], s[vec1[i]]);
		printf("move %s %s\n", aux, s[vec2[i]]);
		std::swap(num[vec1[i]], num[vec2[i]]);
		state[vec1[i]] = state[vec2[i]] = 1;
	}
	std::set <int> set1, set2;
	for (int i = 1; i <= cnt; ++ i){
		set1.insert(i);
	}
	for (int i = cnt + 1; i <= n; ++ i){
		set2.insert(i);
	}
	for (int i = 0; i < n; ++ i){
		if (state[i] == 1){
			if (type[i]){
				set1.erase(num[i]);
			}
			else{
				set2.erase(num[i]);
			}
		}
	}
	for (int i = 0; i < n; ++ i){
		if (state[i] == 2){
			if (type[i]){
				printf("move %s %d\n", s[i], *(set1.begin()));
				set1.erase(set1.begin());
			}
			else{
				printf("move %s %d\n", s[i], *(set2.begin()));
				set2.erase(set2.begin());
			}
		}
	}
	for (int i = 0; i < n; ++ i){
		if (state[i] == 0){
			if (type[i]){
				printf("move %s %d\n", s[i], *(set1.begin()));
				set1.erase(set1.begin());
			}
			else{
				printf("move %s %d\n", s[i], *(set2.begin()));
				set2.erase(set2.begin());
			}
		}
	}
	return 0;
}
