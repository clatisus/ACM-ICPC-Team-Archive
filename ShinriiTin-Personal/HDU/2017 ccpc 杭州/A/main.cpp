/*
题目大意：给出一个只有小写字母的字符串，问至少修改多少位置可以使得任意子串为回文串。
题解：等价于奇数位都相同且偶数位都相同，分别统计一下哪种字母出现最多，都改成它就可以了。 
*/
#include <bits/stdc++.h>

const int max_N = 100 + 21;

int T, n, cnt[2][26];

char s[max_N];

void testCase() {
    scanf("%s", s);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 26; ++j) {
            cnt[i][j] = 0;
        }
    n = strlen(s);
    for (int i = 0; i < n; i += 2) {
        ++cnt[0][s[i] - 'a'];
    }
    for (int i = 1; i < n; i += 2) {
        ++cnt[1][s[i] - 'a'];
    }
    int ans = n, tmp1 = 0, tmp2 = 0;
    for (int i = 0; i < 26; ++i) {
        tmp1 = std::max(tmp1, cnt[0][i]);
        tmp2 = std::max(tmp2, cnt[1][i]);
    }
    ans -= tmp1 + tmp2;
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &T);
    while (T--) testCase();
    return 0;
}
