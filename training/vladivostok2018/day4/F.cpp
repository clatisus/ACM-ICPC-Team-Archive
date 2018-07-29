#include <bits/stdc++.h>

#define MAXS (4000010)
#define mod (1000000007)

char str[MAXS], s[MAXS];
std::stack<char> stack;
std::stack<int> num;

int calc(int a, int b) {
    if (b >= 32) return 0;
    return a >> b;
}

int powmod(int a) {
    int ret = 1ll * a * a % mod;
    return ret;
}

void solve() {
    while (!stack.empty() && stack.top() == 'w') {
        int b = num.top(); num.pop();
        int a = num.top(); num.pop();
        stack.pop();
        num.push(calc(a, b));
    }
}

int main() {
    fgets(s, MAXS, stdin);
    for (int i = 0, j = 0; s[i]; ++ i) {
        if (s[i] == ' ') continue;
        str[j ++] = s[i];
    }
    for (int i = 0; str[i]; ++ i) {
        if (i >= 2 && (isdigit(str[i]) || str[i] == 'S') && str[i - 1] == '>' && str[i - 2] == '>')
            str[i - 2] = ' ', str[i - 1] = 'w';
        if (str[i] == 'S') str[i] = ' ';
    }
    int now = 0, flag = 0;
    for (int i = 0; str[i]; ++ i) {
        if (str[i] == ' ' || str[i] == '\n') continue;
        if (isdigit(str[i])) now = now * 10 + str[i] - '0', flag=1;
        else if (str[i] == '>') {
            if(flag){
                num.push(now);
                solve();
            }
            stack.pop();
            int a = num.top(); num.pop();
            num.push(powmod(a));
            solve();
            now = 0;flag = 0;
        } else if (str[i] == '<') {
            if(flag){
                num.push(now);
                solve();
            }
            stack.push('<');
            now=0;flag=0;
        } else {
            if(flag){
                num.push(now);
                solve();
            }
            stack.push('w');
            now=0;flag=0;
        }
    }
    if(flag){
        num.push(now);
    }
    solve();
    printf("%d\n", num.top());
    return 0;
}
/*
S< S< 12 > > 2 > >
123 >> 1 >> 1
1000000000 >> 129
*/
