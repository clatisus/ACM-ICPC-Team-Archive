#include<bits/stdc++.h>

#define ll long long

ll n;
int len = 0;
std::deque <int> dq;

void solve(ll n){
	if (n == 1){
		return;
	}
	solve(n >> 1);
	dq.push_back(++ len);
	if (n & 1){
		dq.push_front(++ len);
	}
}

int main(){
	scanf("%lld", &n);
	++ n;
	solve(n);
	printf("%d\n", len << 1);
	while ((int) dq.size()){
		printf("%d ", dq.front());
		dq.pop_front();
	}
	for (int i = 1; i <= len; ++ i){
		printf("%d ", i);
	}
	return printf("\n"), 0;
}
