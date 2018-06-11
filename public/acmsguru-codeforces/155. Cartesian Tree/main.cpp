#include <bits/stdc++.h>

const int max_N = 50000 + 21;

using nodeptr = struct node*;

struct node{
	int k, a;
	nodeptr l, r;
	node(int k=0, int a=0):k(k),a(a){
		l = r = nullptr;	
	}
}nodepool[max_N];

struct cmp{
	bool operator()(const nodeptr&x, const nodeptr&y){
		return x -> k < y -> k;
	}
};

int n, top, p[max_N], l[max_N], r[max_N];

nodeptr q[max_N], st[max_N];

#define ID(x) ((x) == nullptr? 0: (x) - nodepool)

int main(){
	scanf("%d", &n);
	for(int i=1,k,a;i<=n;++i){
		scanf("%d%d", &k, &a);
		q[i] = nodepool + i;
		*q[i] = node(k, a);
	}
	std::sort(q+1, q+1+n, cmp());
	for(int i=1;i<=n;++i){
		nodeptr tmp = nullptr;
		while(top && st[top] -> a > q[i] -> a){
			tmp = st[top--];
		}
		q[i] -> l = tmp;
		l[ID(q[i])] = ID(tmp);
		p[ID(tmp)] = ID(q[i]);
		if(top){
			st[top] -> r = q[i];
			r[ID(st[top])] = ID(q[i]);
			p[ID(q[i])] = ID(st[top]);
		}
		st[++top] = q[i];
	}
	puts("YES");
	for(int i=1;i<=n;++i){
		printf("%d %d %d\n", p[i], l[i], r[i]);
	}
	return 0;
}
