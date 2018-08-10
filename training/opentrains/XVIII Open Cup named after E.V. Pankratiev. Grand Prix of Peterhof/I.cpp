#include <bits/stdc++.h>

#define MAXN (1000010)

char s[MAXN];
bool has[4];

int getid(char t) {
    switch (t) {
        case 'N': return 0;
        case 'W': return 1;
        case 'E': return 2;
        case 'S': return 3;
    }
}

char getch(int x) {
    if (x == 0) return 'N';
    if (x == 1) return 'W';
    if (x == 2) return 'E';
    if (x == 3) return 'S';
}

int main() {
    scanf("%s", s);
    int cnt = 0;
    for (int i = 0; s[i]; ++i) {
        int j = getid(s[i]);
        if (!has[j]) {
            has[j] = true;
            ++ cnt;
        }
    }
    if (cnt == 3) {
        for (int i = 0; i < 4; ++i) {
            if (!has[i]) {
                printf("%c\n", getch(i));
                return 0;
            }
        }
    }
    if (cnt == 2) {
        if (has[0] && has[1]) {
            printf("%c%c\n", getch(2), getch(3));
            return 0;
        }
        if (has[0] && has[2]) {
            printf("%c%c\n", getch(1), getch(3));
            return 0;
        }
        if (has[1] && has[3]) {
            printf("%c%c\n", getch(2), getch(0));
            return 0;
        }
        if (has[2] && has[3]) {
            printf("%c%c\n", getch(0), getch(1));
            return 0;
        }
    }
    printf("X\n");
    return 0;
}
