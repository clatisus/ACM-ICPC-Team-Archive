#include<bits/stdc++.h>

const int N = 110;

int x[N][N];
int g[N], ans[N], prev[N], suf[N], left[N], right[N];
int n, m;
double a[N][N], aans[N];
int sit[N];

void answer(){
    putchar('A');
    for (int i = 0; i < n; ++ i){
        printf(" %d", g[i]);
    }
    putchar('\n');
    fflush(stdout);
    exit(0);
}

void gauss(){
    for (int i = 0; i < n; ++ i){
        for (int j = 0; j < n; ++ j){
            a[i][j] = x[j][i];
        }
    }
    for (int i = 0; i < n; ++ i){
        a[i][n] = ans[i];
    }
    for (int i = 0; i < n; ++ i){
        int ssit = -1;
        for (int j = i; j < n; ++ j){
            if (ssit == -1 || std::abs(a[j][i]) > std::abs(a[ssit][i])){
                ssit = j;
            }
        }
        for (int j = i; j <= n; ++ j){
            std::swap(a[i][j], a[ssit][j]);
        }
        for (int j = n; j >= i; -- j){
            a[i][j] /= a[i][i];
        }
        for (int j = 0; j < n; ++ j){
            if (i == j) continue;
            for (int k = n; k >= i; -- k){
                a[j][k] -= a[i][k] * a[j][i];
            }
        }
    }
    for (int i = 0; i < n; ++ i){
        aans[i] = a[i][n];
    }
}

void ask(){
    printf("?");
    for (int i = 0; i < n; ++ i){
        printf(" %d", g[i]);
    }
    putchar('\n');
    fflush(stdout);
    bool flag = true;
    for (int i = 0; i < n; ++ i){
        scanf("%d", &ans[i]);
        if (ans[i]){
            flag = false;
        }
    }
    if (ans[0] == 987654321){
        exit(0);
    }
    if (flag){
        answer();
    }
}

int main(){
    scanf("%d%d", &n, &m);
    if (m == 1){
        for (int i = 0; i < n; ++ i){
            g[i] = 1;
        }
        ask();
    }
    for (int i = 0; i < n; ++ i){
        g[i] = 1;
    }
    ask();
    memcpy(prev, ans, sizeof(ans));
    for (int i = 0; i < n; ++ i){
        g[i] = 2;
        ask();
        for (int j = 0; j < n; ++ j){
            x[i][j] = ans[j] - prev[j];
        }
        g[i] = 1;
    }
    /*for (int i = 0; i < n; ++ i){
        g[i] = m;
    }
    ask();
    memcpy(suf, ans, sizeof(ans));*/
    for (int i = 0; i < n; ++ i){
        left[i] = 1;
        right[i] = m;
    }
    const double eps = 1e-6;
    for (int i = 0; i < 10; ++ i){
        for (int j = 0; j < n; ++ j){
            g[j] = (left[j] + right[j]) >> 1;
        }
        ask();
        gauss();
        /*
        for (int j = 0; j < n; ++ j){
            printf("%.10f%c", aans[j], " \n"[j == n - 1]);
        }*/
        for (int j = 0; j < n; ++ j){
            if (aans[j] > eps){
                right[j] = g[j] - 1;
            }
            else if (aans[j] < -eps){
                left[j] = g[j] + 1;
            }
        }
    }
    return 0;
}

