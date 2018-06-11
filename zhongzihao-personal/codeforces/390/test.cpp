#include<bits/stdc++.h>

int main(){
	int *p1, *p2;
	p1 = new int;
	p2 = new int;
	*p1 = 11;
	*p2 = 0;
	p2 = p1;
	std::cout << *p1 << ' ' << *p2 << std::endl;
	delete p1;
	delete p2;
	return 0;
}
