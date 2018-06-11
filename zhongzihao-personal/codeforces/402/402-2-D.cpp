#include<bits/stdc++.h>

const int N = 200010;

int len, a[N];
char t[N], p[N], str[N];

bool check(int n){
	memset(str, 0, sizeof(str));
	for (int i = len - 1; i >= len - n; -- i){
		str[a[i]] = t[a[i]];
	}
	int lenp = strlen(p), j = 0;
	for (int i = 0; i < len && j < lenp; ++ i){
		while (i < len && p[j] != str[i]){
			++ i;
		}
		if (p[j] == str[i]){
			++ j;
		}
	}
	if (j == lenp){
		return true;
	}
	return false;
}

int main(){
	scanf("%s%s", t, p);
	len = strlen(t);
	for (int i = 0; i < len; ++ i){
		scanf("%d", &a[i]);
		-- a[i];
	}
	int left = 1, right = len;
	while (left < right){
		int mid = left + right >> 1;
		if (check(mid)){
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	return printf("%d\n", len - left), 0;
}
