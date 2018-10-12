#include<bits/stdc++.h>

char s[100];
std::vector <std::string> ans;

const int N = 60;

int a[N][N];
int xx[N], yy[N];
int tmp[N][N];

void print(int &x1, int &y1, int x2, int y2){
    sprintf(s, "%d %d %d %d\n", x1 + 1, y1 + 1, x2 + 1, y2 + 1);
    std::swap(a[x1][y1], a[x2][y2]);
    x1 = x2, y1 = y2;
    ans.push_back(s);
}

int main(){
    memset(a, -1, sizeof(a));
    memset(tmp, -1, sizeof(tmp));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i){
        scanf("%d%d", &x[i], &y[i]);
        -- x[i], -- y[i];
        a[x[i]][y[i]] = i;
    }
    for (int i = 0; i < m; ++ i){
        scanf("%d%d", &xx[i], &yy[i]);
        -- xx[i], -- yy[i];
        tmp[xx[i]][yy[i]] = i;
    }
    if (n == 1){
        puts("0");
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i < n; ++ i){
        if (a[0][i] != -1){
            int x = 0, y = i;
            while (y > cnt){
                print(x, y, x, y - 1);
            }
            ++ cnt;
        }
    }
    for (int i = 1; i < n; ++ i){
        for (int j = n - 1; j >= 0; -- j){
            if (a[i][j] != -1){
                if (j >= cnt){
                    int x = i, y = j;
                    while (x > 0){
                        print(x, y, x - 1, y);
                    }
                    while (y > cnt){
                        print(x, y, x, y - 1);
                    }
                }
                else{
                    while (y < cnt){
                        print(x, y, x, y + 1);
                    }
                    while (x > 0){
                        print(x, y, x - 1, y);
                    }
                }
                ++ cnt;
            }
        }
    }
    for (int i = n - 1; i >= 2; -- i){
        for (int j = 0; j < m; ++ j){
            if (xx[j] == i){
                int x = 0, y;
                for (int k = 0; k < n; ++ k){
                    if (a[0][k] == j){
                        sit = k;
                        break;
                    }
                }
                while (x < i - 1){
                    print(x, y, x + 1, y);
                }
                if (y > yy[j]){
                    while (y > yy[j]){
                        print(x, y, x, y - 1);
                    }
                }
                else{
                    while (y < yy[j]){
                        print(x, y, x, y + 1);
                    }
                }
                print(x, y, x + 1, y);
            }
        }
    }
    cnt = 0;
    for (int i = 0; i < n; ++ i){
        if (a[0][i] != -1){
            int x = 0, y = i;
            while (y > cnt){
                print(x, y, x, y - 1);
            }
            ++ cnt;
        }
    }
    int ccnt = n - 1;
    for (int i = n - 1; i >= 0; -- i){
        if (tmp[0][i] != 0){
            int x = 0, y;
            for (int j = 0; j < cnt; ++ j){
                if (a[0][j] == tmp[0][i]){
                    y = j;
                    break;
                }
            }
            print(x, y, x + 1, y);
            while (y < ccnt){
                print(x, y, x, y + 1);
            }
            print(x, y, x - 1, y);
            -- ccnt;
        }
    }
    printf("%d\n", (int) ans.size());
    for (auto u : ans){
        std::cout << u;
    }
    return 0;
}
