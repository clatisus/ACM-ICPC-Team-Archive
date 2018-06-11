#include<bits/stdc++.h>

std::map <int, int> Hash;

int n;

int main(){
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		if (x > 3200){
			x = 3200;
		}
		++ Hash[x / 400];
	}
	int min = Hash.size(), max = min;
	if (Hash.count(8)){
		min = std::max(min - 1, 1);
		max = max - 1 + Hash[8];
	}
	printf("%d %d\n", min, max), 0;
}
