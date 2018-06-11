#include<bits/stdc++.h>

const int N = 100010;
typedef long long ll;

int aux[N];

struct perm{
	static const int N = 100010;

	int &operator [](const int &n){return a[n];}

	int n;
	int a[N];
};

void change(perm &p, perm &q){
	for (int i = 1; i <= p.n; ++ i){
		aux[i] = p[q[i]];
	}
	for (int i = 1; i <= p.n; ++ i){
		p[i] = aux[i];
	}
}

perm p, q, aaux;
int x[N];

int main(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i){
		scanf("%d", &x[i]);
	}
	int m;
	ll k;
	scanf("%d%lld", &m, &k);
	p.n = n;
	for (int i = 1; i <= n; ++ i){
		p[i] = i;
	}
	for (int i = 0, x; i < m; ++ i){
		scanf("%d", &x);
		std::swap(p[x - 1], p[x]);
	}
	q.n = n;
	for (int i = 1; i <= n; ++ i){
		q[i] = i;
	}
	for ( ; k > 0; k >>= 1){
		if (k & 1){
			change(q, p);
		}
		aaux = p;
		change(p, aaux);
	}
	ll now = x[1];
	for (int i = 1; i <= n; ++ i){
		printf("%lld.0\n", now);
		now += x[q[i] + 1] - x[q[i]];
	}
	return 0;
}
