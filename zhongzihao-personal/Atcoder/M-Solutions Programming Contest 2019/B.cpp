#include <bits/stdc++.h>

const int N = 20;

char s[N];

int main() {
    scanf("%s", s);
    int n = strlen(s);
    int cnt = 15 - n;
    for (int i = 0; i < n; ++i) {
        cnt += s[i] == 'o';
    }
    puts(cnt >= 8 ? "YES" : "NO");
    return 0;
}
