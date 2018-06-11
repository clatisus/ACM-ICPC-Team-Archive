/*
�۲���5�ֲ�����ֻ��������̬��ͬ��λ�õ������йأ���˿�����90x90�ľ���ת�ƣ�����ֶ������һ��
ֱ�Ӿ���˷������ݻ�tle(90^3log(T))�� �ı�˷�˳�������һ��1xn��������֮��ĳ˷����Ӷȶ���Ϊ90^2���Ϳ���ͨ���� 
*/ 

#include <bits/stdc++.h>

const int mod = (int)1e9 + 7;
const int st = 11;
const int size = 90;

struct Mat{
	int n, m, a[size][size];
	Mat(int n = 0, int m = 0):n(n), m(m){ 
		memset(a, 0, sizeof(a));
	}
	Mat operator*(const Mat&o)const{
		Mat res(n, o.m);
		for(int i = 0; i < n; ++ i)
			for(int k = 0; k < m; ++ k)
				for(int j = 0; j < o.m; ++ j){
					res.a[i][j] = (res.a[i][j] + 1ll*a[i][k]*o.a[k][j])%mod;
				}
		return res;
	}
};

Mat A[30];

inline int C2(int n){
	return (n * (n-1) >> 1);
}

int main(){
	A[0] = Mat(90, 90);
	for(int s=1;s<=90;++s){
		A[0].a[s-1][s-1] = s*(90-s);
		if(s>1) A[0].a[s-1][s-2] = s;
		if(s<90) A[0].a[s-1][s] = (90 - s);
		if(s>2) A[0].a[s-1][s-3] = C2(s);
		if(s<89) A[0].a[s-1][s+1] = C2(90-s);
	}
	
	for(int i=1;i<30;++i) A[i] = A[i-1] * A[i-1];
	
	int T, n;
	
	scanf("%d", &T);
	
	while(T --){
		scanf("%d", &n);
		Mat res(1, 90);
		res.a[0][st-1] = 1;
		for(int i=0,k=n-1;k;++i,k>>=1)
			if(k&1) res = res * A[i];
		int ans = (res.a[0][0] + res.a[0][1])%mod;
		printf("%d\n", ans);
	}
	
	return 0;
}

