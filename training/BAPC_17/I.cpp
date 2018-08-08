#include<bits/stdc++.h>

const int N = 110;

int main(){
    int p, q;
    scanf("%d%d", &p, &q);
    if ((p & 1) == 0) puts("0");
    else if ((p & 1) && (q & 1) ) puts("1");
    else if ((p & 1) && ((q & 1) == 0)) {
        if (p < q) puts("2");
        else puts("0");
    }
    return 0;
}
