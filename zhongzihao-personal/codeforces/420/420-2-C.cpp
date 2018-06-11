#include<bits/stdc++.h>

const int N = 300010;

char s[N];
int n;
int stack[N];

int main(){
	scanf("%d", &n);
	int now = 1, top = 0, ans = 0;
	for (int i = 0; i < n << 1; ++ i){
		scanf("%s", s);
		if (s[0] == 'a'){
			int op;
			scanf("%d", &op);
			stack[top ++] = op;
		}
		else{
			if (stack[top - 1] != now){
				++ ans;
				std::sort(stack, stack + top, std::greater <int>());
			}
			-- top;
			++ now;
		}
	}
	return printf("%d\n", ans), 0;
}
