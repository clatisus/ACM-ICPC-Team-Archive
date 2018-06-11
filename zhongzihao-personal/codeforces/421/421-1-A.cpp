#include<bits/stdc++.h>

const int N = 100;

int a, b, l, r;
bool vis[N];

int main(){
	scanf("%d%d%d%d", &a, &b, &l, &r);
	-- l, -- r;
	if (r - l + 1 >= 4 * (a + b)){
		return printf("%d\n", a > b ? 2 * a - b : a + 1), 0;
	}
	for (int i = l; i <= r; ++ i){
		int x = i / (a + b), remx = i % (a + b);
		if (a > b){
			if (remx >= a){
				remx = a - 1;
			}
			if (remx >= b){
				if (x & 1){
					vis[remx + a - b] = true;
				}
				else{
					vis[remx] = true;
				}
			}
			else{
				vis[remx] = true;
			}
		}
		else{
			if (remx >= a){
				remx = a - 1;
			}
			if (remx >= a - 1){
				if (x & 1){
					vis[remx + 1] = true;
				}
				else{
					vis[remx] = true;
				}
			}
			else{
				vis[remx] = true;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i < N; ++ i){
		ans += vis[i];
	}
	return printf("%d\n", ans), 0;
}
