#include <bits/stdc++.h>

#define MAXN (100010)

int n;
char s[MAXN];
int left[MAXN], right[MAXN];

char vowel(char t) {
    if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u') {
        return '0';
    }
    return '1';
}

int testCase() {
    n = strlen(s);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        s[i] = vowel(s[i]);
        cnt += s[i] == '1';
    }
    if (cnt == 0 || cnt == n) return 1;
    if (s[0] == '1') return 0;
    if (s[n - 1] == '1') s[n++] = '0';

    int pre = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') continue;
        left[i] = pre;
        pre = i;
    }
    int suf = n;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '1') continue;
        right[i] = suf;
        suf = i;
    }
    int l = 0, r = n - 1;
    while (true) {
        if (l == left[r]) return r - l;
        r = left[r];
        if (right[l] == r) return r - l;
        l = right[l];
    }
}

int main() {
    while (~scanf("%s", s)) {
        printf("%d\n", testCase());
    }
    return 0;
}

