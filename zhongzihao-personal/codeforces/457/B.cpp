#include<bits/stdc++.h>

typedef long long ll;

int main(){
	ll n;
	int k;
	scanf("%I64d%d", &n, &k);
	std::priority_queue <int> pq;
	for (int i = 0; i < 62; ++ i){
		if (n >> i & 1){
			pq.push(i);
		}
	}
	if ((int) pq.size() > k){
		puts("No");
		return 0;
	}
	while ((int) pq.size() < k){
		int x = pq.top();
		pq.pop();
		pq.push(x - 1);
		pq.push(x - 1);
	}
	puts("Yes");
	while (!pq.empty()){
		printf("%d ", pq.top());
		pq.pop();
	}
	return 0;
}
