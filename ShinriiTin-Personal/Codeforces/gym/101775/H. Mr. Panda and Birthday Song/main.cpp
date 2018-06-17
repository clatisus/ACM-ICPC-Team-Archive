#include <bits/stdc++.h>

const int max_N = (int) 1e6 + 21;
const int inf = 0x3f3f3f3f;

int T, n, x, y, f[2][max_N];

char s[max_N];

bool isVowel(char c) {
    static const std::string vowel("aeiou");
    return vowel.find(c) != std::string::npos;
}

void testCase() {
    scanf("%s%d%d", s + 1, &x, &y);
    n = strlen(s + 1);
    memset(f[0] + 1, 0x3f, sizeof(int) * n);
    memset(f[1] + 1, 0x3f, sizeof(int) * n);
    f[0][0] = f[1][0] = 0;
    auto trans = [&](const int tp, const int i) {
        if (f[tp ^ 1][i - 1] < inf) {
            f[tp][i] = 1;
        } else {
            f[tp][i] = f[tp][i - 1] + 1;
        }
    };
    bool like = true;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == '?') {
            trans(0, i);
            trans(1, i);
        } else {
            trans(isVowel(s[i]), i);
        }
        if (f[0][i] >= y && f[1][i] >= x) {
            like = false;
            break;
        }
        if (f[0][i] >= y) f[0][i] = inf;
        if (f[1][i] >= x) f[1][i] = inf;
    }
    /*
    for (int i = 1; i <= n; ++i) {
        printf("f[0][%d] = %d, f[1][%d] = %d\n", i, f[0][i], i, f[1][i]);
    }
     */
    bool dislike = false;
    for (int i = 1, cnt = 0; i <= n; ++i) {
        if (s[i] != '?' && isVowel(s[i])) {
            cnt = 0;
        } else {
            if (++cnt >= y) dislike = true;
        }
    }
    for (int i = 1, cnt = 0; i <= n; ++i) {
        if (s[i] != '?' && !isVowel(s[i])) {
            cnt = 0;
        } else {
            if (++cnt >= x) dislike = true;
        }
    }
    static int caseNo = 0;
    printf("Case #%d: ", ++caseNo);
    if (like && dislike) puts("SURPRISE");
    else puts(like ? "LIKE" : "DISLIKE");
}

int main() {
    for (scanf("%d", &T); T--; testCase());
    return 0;
}