#include <bits/stdc++.h>

const int max_N = 1e3 + 21;

int n;

bool vis[4];

char s[max_N];

int main(){
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;++i){
		switch(s[i]){
			case('N'): vis[0]=1; break;	
			case('S'): vis[1]=1; break;
			case('E'): vis[2]=1; break;
			case('W'): vis[3]=1; break;
		}
	}
	if((vis[0]^vis[1])||(vis[2]^vis[3]))puts("No");
	else puts("Yes");
	return 0;
}

