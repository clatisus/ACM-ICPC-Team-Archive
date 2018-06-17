/**
 * @题目大意：给出一个由小写字母和?组成的字符串，长度不超过10^6，问是否存在一种将?换成字母的方法，使得任意连续的元音字母少于x个，任意连续的辅音字母少于y个，同时问是否可以不满足这个条件。
 * @题解：不满足的就贪心全部换成元音字母或辅音字母判断一下，满足则用f[0/1][i]进行dp，计算第i位是否为辅音字母时在i处至少由多少个连续的同为元音或辅音的数量即可。
 */
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
    bool dislike = !like;
    for (int i = 1, cnt = 0; !dislike && i <= n; ++i) {
        if (s[i] != '?' && isVowel(s[i])) {
            cnt = 0;
        } else {
            if (++cnt >= y) dislike = true;
        }
    }
    for (int i = 1, cnt = 0; !dislike && i <= n; ++i) {
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