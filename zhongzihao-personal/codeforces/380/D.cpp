#include<bits/stdc++.h>

typedef unsigned int uint;
const int N = 4010;

inline uint calc(int l, int r, int i, int pre){
	l = l << 12 | r;
	l = l << 1 | i;
	l = l << 7 | pre;
	return l;
}

std::unordered_map <uint, int> Hash;

int a[N], prefix[N];

int dfs(uint state){
	if (Hash.count(state)){
		return Hash[state];
	}
	int pre = state & 0x7f;
	int i = state >> 7 & 1;
	int r = state >> 8 & 0xfff;
	int l = state >> 20;
	if (r - l + 1 < pre){
		return 0;
	}
	if (!i){
		int max = prefix[l + pre - 1] - prefix[l - 1] - dfs(calc(l + pre, r, i ^ 1, pre));
		if (r - l >= pre){
			max = std::max(max, prefix[l + pre] - prefix[l - 1] - dfs(calc(l + pre + 1, r, i ^ 1, pre + 1)));
		}
		return Hash[state] = max;
	}
	int max = prefix[r] - prefix[r - pre] - dfs(calc(l, r - pre, i ^ 1, pre));
	if (r - l >= pre){
		max = std::max(max, prefix[r] - prefix[r - pre - 1] - dfs(calc(l, r - pre - 1, i ^ 1, pre + 1)));
	}
	return Hash[state] = max;
}

int main(){
	int n;
	//scanf("%d", &n);
	n = 4000;
	for (int i = 1; i <= n; ++ i){
		//scanf("%d", &a[i]);
		a[i] = i;
		prefix[i] = prefix[i - 1] + a[i];
	}
	printf("%d\n", dfs(calc(1, n, 0, 1)));
	return 0;
}
