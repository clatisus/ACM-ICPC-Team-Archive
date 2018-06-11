#include <bits/stdc++.h>

void generate(FILE* file, int n){
	fprintf(file, "%d\n", n);
	int p[n]; for(int i=0;i<n;++i) p[i] = i;
	int cnt = 3;
	while(cnt --){
		std::random_shuffle(p, p+n);
		for(int i=0;i<n;++i) fprintf(file, "%d%c", p[i]+1, " \n"[i==n-1]);
	}
}

int randInt(int n){
	return (rand()<<16|rand())%n + 1;
}

const int T = 15;

void genereteCases(){
	generate(fopen("./data/input0.txt", "w"), 50);
	generate(fopen("./data/input1.txt", "w"), 50);
	generate(fopen("./data/input2.txt", "w"), 50);
	
	generate(fopen("./data/input3.txt", "w"), 500);
	generate(fopen("./data/input4.txt", "w"), 500);
	generate(fopen("./data/input5.txt", "w"), 500);
	
	generate(fopen("./data/input6.txt", "w"), 5000);
	generate(fopen("./data/input7.txt", "w"), 5000);
	generate(fopen("./data/input8.txt", "w"), 5000);
	
	generate(fopen("./data/input9.txt", "w"), 50000);
	generate(fopen("./data/input10.txt", "w"), 50000);
	generate(fopen("./data/input11.txt", "w"), 50000);
	
	generate(fopen("./data/input12.txt", "w"), 100000);
	generate(fopen("./data/input13.txt", "w"), 100000);
	generate(fopen("./data/input14.txt", "w"), 100000);
}

using String = std::string;

String int2String(int x){
	char a = '0' + (x/10);
	char b = '0' + (x%10);
	String res = "";
	if(a!='0') res += a;
	res += b;
	return res;
}

void solveCases(){
	String filename = "./data/input";
	for(int t=0;t<T;++t){
		String fin = filename + int2String(t) + ".txt";
		String fout = filename + int2String(t) + ".out";
		
		printf("Debug: %s %s\n", fin.c_str(), fout.c_str());
		
		system(("main < " + fin + " > " + fout).c_str());
	}
}

void transfer(){
	FILE* fout;
	fout = fopen("./data.in", "w");
	fprintf(fout, "%d\n", T);
	String filename = "./data/input";
	for(int t=0;t<T;++t){
		String file = filename + int2String(t) + ".txt";
		FILE* fin = fopen(file.c_str(), "r");
		char c;
		while((c = fgetc(fin))!=EOF) fputc(c, fout);
	}
	fout = fopen("./data.out", "w");
	filename = "./data/input";
	for(int t=0;t<T;++t){
		String file = filename + int2String(t) + ".out";
		FILE* fin = fopen(file.c_str(), "r");
		char tmp[10];
		long long a, b, c, d;
		fscanf(fin, "%s%lld%lld%lld%lld", tmp, &a, &b, &c, &d);
		fprintf(fout, "%lld\n", d);
	}
}

int main(){
	srand(time(0));
//	generate(fopen("input.txt", "w"), randInt(200));
//	genereteCases();
//	solveCases();
	transfer();
	return 0;
}
