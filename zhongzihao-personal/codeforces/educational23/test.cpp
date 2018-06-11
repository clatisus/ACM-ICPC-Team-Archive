#include<bits/stdc++.h>

int main(){
	int b = 0;
	int &a = ++ b;
	return printf("%d\n", &a == &b), 0;
}
