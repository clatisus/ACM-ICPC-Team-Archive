#include <bits/stdc++.h>

const int max_M = 100 + 21;

int N,M,cnt,A[max_M],b[max_M];

int main(){
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;++i){
		scanf("%d",A+i);
		if(A[i]&1)++cnt;
	}
	if(M==1){
		if(N==1)puts("1\n1\n1");
		else printf("%d\n2\n%d 1\n",N,N-1);
	}
	else{
		if(cnt>2)puts("Impossible");
		else{
			for(int i=1;i<=M;++i)
				if(A[i]&1){
					std::swap(A[1],A[i]);
					break;	
				}
			for(int i=M;i>1;--i)
				if(A[i]&1){
					std::swap(A[i],A[M]);
					break;	
				}
			for(int i=1;i<=M;++i)
				printf("%d%c",A[i]," \n"[i==M]);
			memcpy(b+1,A+1,sizeof(int)*M);
			--b[1],++b[M];
			if(!b[1]){
				printf("%d\n",M-1);
				for(int i=2;i<=M;++i)
					printf("%d%c",b[i]," \n"[i==M]);
			}
			else{
				printf("%d\n",M);
				for(int i=1;i<=M;++i)
					printf("%d%c",b[i]," \n"[i==M]);
			}
		}
	}
	return 0;
}
