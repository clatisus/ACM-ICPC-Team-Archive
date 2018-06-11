#include<bits/stdc++.h>
 
const int N = 4010;
 
std::vector <int> vec;
 
int a, b, n;
int ans[N];
char s[N];
 
int main(){
	scanf("%d%d", &a, &b);
	n = a + b;
	if (a <= b){
		return printf("Impossible\n"), 0;
	}
	for (int i = 0; i < n; ++ i){
		if (!vec.size()){
			vec.push_back(i);
			continue;
		}
		printf("? %d %d\n", i, vec.back());
		fflush(stdout);
		int x;
		scanf("%s", s);
		if (s[0] == 'Y'){
			vec.push_back(i);
		}
		else{
			vec.pop_back();
		}
	}
	int honest = vec.front();
	for (int i = 0; i < n; ++ i){
		printf("? %d %d\n", honest, i);
		fflush(stdout);
		scanf("%s", s);
		ans[i] = s[0] == 'Y';
	}
	printf("!");
	for (int i = 0; i < n; ++ i){
		printf("%d", ans[i]);
	}
	return printf("\n"), 0;
}
