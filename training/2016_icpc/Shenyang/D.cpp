#include <bits/stdc++.h>

#define N (256)

short f[2][N][N][N];

void init() {
    for (int p = 0; p < 2; ++p) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (j > k) f[p][1][j][k] = 1;
                else if (j < k) f[p][1][j][k] = 0;
                else f[p][1][j][k] = (p & 1);
            }
        }
    }
    for (int i = 2; i < N; ++i) {
        for (int p = 0; p < 2; ++p) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (j == k) {
                        f[p][i][j][k] = (i / 2) + (p & i & 1);
                        continue;
                    }
                    short &c = f[p][i][j][k];
                    auto ff = f[p ^ 1][i - 1];
                    if (p) {
                    // Alice
                        short a = ff[j - 0][k] + 1;
                        short b;
                        for (int x = 0; ; ++x) {
                            if (x + 1 > k || (b = ff[j][k - x - 1]) >= a) {
                                c = a;
                                break;
                            }

                            if (x + 1 > j || (a = ff[j - x - 1][k] + 1) <= b) {
                                c = b;
                                break;
                            }
                        }
                    } else {
                    // Bob
                        short a;
                        short b = ff[j][k - 0];
                        for (int x = 0; ; ++x) {
                            if (x + 1 > j || (a = ff[j - x - 1][k] + 1) <= b) {
                                c = b;
                                break;
                            }

                            if (x + 1 > k || (b = ff[j][k - x - 1]) >= a) {
                                c = a;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
//auto a = clock();
    init();
    //printf("%d\n", (int)(clock() - a) / 1000);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, a, b;
        scanf("%d%d%d", &n, &a, &b);
        int alice = f[1][n][a][b];
        int bob = n - alice;
        printf("Alice %d Bob %d\n", alice, bob);
    }
    return 0;
}

