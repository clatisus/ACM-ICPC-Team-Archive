#include<bits/stdc++.h>

const int N = 100010;

int pres[N][2], pret[N][2];
char s[N], t[N];

int main(){
	scanf("%s%s", s + 1, t + 1);
	int lens = strlen(s + 1), lent = strlen(t + 1);
	for (int i = 1; i <= lens; ++ i){
		for (int j = 0; j < 2; ++ j){
			pres[i][j] = pres[i - 1][j];
		}
		++ pres[i][s[i] - 'A'];
	}
	for (int i = 1; i <= lent; ++ i){
		for (int j = 0; j < 2; ++ j){
			pret[i][j] = pret[i - 1][j];
		}
		++ pret[i][t[i] - 'A'];
	}
	int q;
	scanf("%d", &q);
	while (q --){
		int l1, r1, l2, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		int x1 = pres[r1][0] - pres[l1 - 1][0] + (pres[r1][1] - pres[l1 - 1][1] << 1);
		int x2 = pret[r2][0] - pret[l2 - 1][0] + (pret[r2][1] - pret[l2 - 1][1] << 1);
		printf((x2 - x1) % 3 ? "NO\n" : "YES\n");
	}
	return 0;
}
