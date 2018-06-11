#include <bits/stdc++.h>

int main(){
	std::vector<std::pair<int,int>> data = {
		{50, 25},
		{50, 50},
		{50, 1},
		
		{500, 9},
		{500, 100},
		{500, 411},
		
		{5000, 37},
		{5000, 998},
		{5000, 2333},
		
		{50000, 13},
		{50000, 1111},
		{50000, 6655},
		
		{200000, 1777},
		{200000, 23333},
		{200000, 114514},
	};
	
	int T = data.size();

	FILE* file = fopen("data.in", "w");
	
	fprintf(file, "%d\n", T);
	
	auto myRand = [](int n){
		return (rand()<<16|rand())%n;
	};
	
	auto generate = [&](std::pair<int,int> Case){
		srand(time(0));
		int n = Case.first, k = Case.second;
		fprintf(file, "%d %d\n", n, k);
		int q[n]; 
		for(int i=0;i<n;++i) q[i] = myRand((int)1e9) + 1;
		std::sort(q, q+n);
		int b[n]; 
		for(int i=0;i<n;++i){ 
			if(n-i-1>k && rand()&1) b[i] = k + myRand(n-i-1-k);
			else b[i] = myRand(n-i);
		}
		int p[n];
		for(int i=n-1;~i;--i){
			int k = (n-i) - (n-i-b[i]);
			for(int j=n-i-1;j>=k;--j) p[j+1] = p[j];
			p[k] = i;
		}
		for(int i=0;i<n;++i) fprintf(file, "%d\n", q[p[i]]);
	};
	
	for(auto&Case:data) generate(Case);
	
	return 0;
}
