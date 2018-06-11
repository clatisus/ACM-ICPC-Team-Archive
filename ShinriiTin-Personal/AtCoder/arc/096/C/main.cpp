#include <bits/stdc++.h>
 
int main(){
    int A, B, C, X, Y;
    scanf("%d%d%d%d%d", &A, &B, &C, &X, &Y);
    int ans = ~0U>>1;
    for(int i=0;i<=X||i<=Y;++i){
        int tmp = i*C*2 + std::max(0, X-i)*A + std::max(0, Y-i)*B;
        ans = std::min(ans, tmp);
    }
    printf("%d\n", ans);
    return 0;
}
