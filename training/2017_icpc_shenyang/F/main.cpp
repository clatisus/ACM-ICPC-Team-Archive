#include<bits/stdc++.h>

std::vector <__int128> ans;

void read(__int128 &x){
    x = 0;
    char ch;
    while (!isdigit(ch = getchar()));
    x = ch - '0';
    while (isdigit(ch = getchar())){
        x = x * 10 + ch - '0';
    }
}

void print(__int128 x){
    if (x < 10){
        putchar(x + '0');
    }
    else{
        print(x / 10);
        putchar(x % 10 + '0');
    }
}

void init(){
    __int128 x = 4, y = 2;
    while (x < 1e31){
        ans.push_back(x);
        //print(x);
        //putchar('\n');
        __int128 tmpx = 4 * x + 6 * y;
        __int128 tmpy = 2 * x + 4 * y;
        tmpx >>= 1, tmpy >>= 1;
        x = tmpx;
        y = tmpy;
    }
}

void solve(){
    __int128 x;
    read(x);
    print(*std::lower_bound(ans.begin(), ans.end(), x));
    putchar('\n');
}

int main(){
    init();
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
