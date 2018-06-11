#include <bits/stdc++.h>

int a,b;

int main(){
	scanf("%d%d",&a,&b);
	if(a<=0&&0<=b)puts("Zero");
	else if(a>0)puts("Positive");
	else puts(((b-a)&1)?"Positive":"Negative");
	return 0;
}
