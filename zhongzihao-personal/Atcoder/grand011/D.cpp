#include<bits/stdc++.h>

const int N = 200010;

char s[N];
int n, k;
std::deque <int> dq;

int main(){
	scanf("%d%d%s", &n, &k, s);
	for (int i = 0; i < n; ++ i){
		dq.push_back(s[i] - 'A');
	}
	if (k > n << 1){
		k = (n << 1) + (k & 1);
	}
	int flag = 0;
	for (int i = 0; i < k; ++ i){
		int x = dq.front();
		if (x == flag){
			dq.pop_front();
			dq.push_front(flag ^ 1);
		}
		else{
			dq.pop_front();
			flag ^= 1;
			dq.push_back(flag);
		}
	}
	while (!dq.empty()){
		int x = dq.front();
		putchar((x ^ flag) + 'A');
		dq.pop_front();
	}
	return printf("\n"), 0;
}
