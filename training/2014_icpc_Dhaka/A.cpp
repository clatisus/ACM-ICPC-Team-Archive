#include <bits/stdc++.h>

#define MAXS (1000010)

char s[MAXS];
int map[26];

int main() {
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%s", s);
        int m;
        scanf("%d", &m);
        for (int i = 0; i < 26; ++i) map[i] = i;
        while (m --) {
            char a[10], b[10];
            scanf("%s%s", a, b);
            for (int i = 0; i < 26; ++i) {
                if (map[i] == b[0] - 'A') {
                    map[i] = a[0] - 'A';
                }
            }
        }
        for (int i = 0; s[i]; ++i) {
            if (s[i] == '_') continue;
            s[i] = map[s[i] - 'A'] + 'A';
        }
        printf("%s\n", s);
    }
    return 0;
}
