#include<bits/stdc++.h>

int main(){
	int n;
	scanf("%d", &n);
	std::set <int> set;
	for (int i = 0, x; i < n; ++ i){
		scanf("%d", &x);
		if (set.count(x)){
			set.erase(x);
		}
		else{
			set.insert(x);
		}
	}
	return printf("%d\n", (int) set.size()), 0l;
}
