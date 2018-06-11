#include<bits/stdc++.h>

const int N = 100010;
const int INF = 0xf0f0f0f;

char a[N], b[N];
int pre[N], suf[N];

int main(){
	memset(pre, 0xf, sizeof(pre));
	memset(suf, 0xf, sizeof(suf));
	scanf("%s%s", a, b);
	int lena = strlen(a), lenb = strlen(b);
	for (int i = 0, j = 0; i < lenb, j < lena; ++ i){
		while (a[j] != b[i] && j < lena){
			++ j;
		}
		if (j < lena){
			pre[i] = j ++;
		}
	}
	for (int i = lenb - 1, j = lena - 1; i >= 0, j >= 0; -- i){
		while (a[j] != b[i] && j >= 0){
			-- j;
		}
		if (j >= 0){
			suf[i] = j --;
		}
	}
	int min = INT_MAX, left, right;
	for (int i = 0; j = 0; i < lenb; ++ i){
		while (j < lenb && pre[i] + suf[j] > lena - 1){
			++ j;
		}
		if (pre[i] + suf[j] < min){
			min = pre[i] + suf[j];
			left = i;
			right = j;
		}
	}
	
}
