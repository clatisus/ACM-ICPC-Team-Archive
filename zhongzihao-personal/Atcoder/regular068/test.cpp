#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int MM = 1e9 + 7;
 
int n, m;
int K;
ll pw[2222];
ll sum[2222][2222];
 
void solve(int casi){
	cin>>n>>K;
	pw[0] = 1;
	for(int i = 1; i <= 2000; i++){
		pw[i] = (2 * pw[i-1]) % MM;
	}
	for(int i = 0; i <= n; i++)
		sum[0][i] = 1;
	for(int i = 1; i < K; i++){
		sum[i][0] = sum[i - 1][1];
		for(int j = 1; j <= n - i; j++){
			sum[i][j] = (sum[i][j-1] + sum[i-1][j+1]) % MM;
		}
	}
	cout<<((K!=n)?(sum[K - 1][n - K] * pw[n-K-1] % MM):sum[K - 1][n - K])<<endl;
}
 
 
int main(){
	solve(1);
	return 0;
}
