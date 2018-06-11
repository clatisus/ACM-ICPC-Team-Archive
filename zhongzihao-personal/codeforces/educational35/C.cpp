#include<bits/stdc++.h>

int cnt[10000];

int main(){
	int k1, k2, k3;
	scanf("%d%d%d", &k1, &k2, &k3);
	++ cnt[k1], ++ cnt[k2], ++ cnt[k3];
	if (cnt[1] >= 1 || cnt[2] >= 2 || cnt[3] >= 3){
		puts("YES");
	}
	else if (cnt[2] == 1 && cnt[4] == 2){
		puts("YES");
	}
	else{
		puts("NO");
	}
	return 0;
}
