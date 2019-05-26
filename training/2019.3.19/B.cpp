#include <bits/stdc++.h>

const int N = 1010;

char s[N][N], t[N][N];
bool rtwo[N], ctwo[N];
bool rtwo2[N], ctwo2[N];

void error(){
    puts("0");
    exit(0);
}

int main(){
    int r, c;
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; ++ i){
        scanf("%s", s[i]);
    }
    for (int i = 0; i < r; ++ i){
        scanf("%s", t[i]);
    }
    for (int i = 0; i < r; ++ i){
        int cnt = 0;
        for (int j = 0; j < c; ++ j){
            cnt += t[i][j] == 'X';
        }
        rtwo[i] = cnt >= 2;
    }
    for (int j = 0; j < c; ++ j){
        int cnt = 0;
        for (int i = 0; i < r; ++ i){
            cnt += t[i][j] == 'X';
        }
        ctwo[j] = cnt >= 2;
    }
    for (int i = 0; i < r; ++ i){
        for (int j = 0; j < c; ++ j){
            if (rtwo[i] && ctwo[j] && s[i][j] != t[i][j]){
                error();
            }
        }
    }
    for (int i = 0; i < r; ++ i){
        if (rtwo[i]){
            continue;
        }
        bool flag1 = true, flag2 = true;
        for (int j = 0; j < c; ++ j){
            if (!ctwo[j]){
                continue;
            }
            if (t[i][j] != 'O'){
                flag1 = false;
            }
            if (t[i][j] != s[i][j]){
                flag2 = false;
            }
        }
        if (!flag1){
            if (!flag2){
                error();
            }
            rtwo2[i] = true;
        }
    }
    for (int j = 0; j < c; ++ j){
        if (ctwo[j]){
            continue;
        }
        bool flag1 = true, flag2 = true;
        for (int i = 0; i < r; ++ i){
            if (!rtwo[i]){
                continue;
            }
            if (t[i][j] != 'O'){
                flag1 = false;
            }
            if (t[i][j] != s[i][j]){
                flag2 = false;
            }
        }
        if (!flag1){
            if (!flag2){
                error();
            }
            ctwo2[j] = true;
        }
    }
    for (int i = 0; i < r; ++ i){
        rtwo[i] = rtwo[i] || rtwo2[i];
    }
    for (int j = 0; j < c; ++ j){
        ctwo[j] = ctwo[j] || ctwo2[j];
    }
    bool hasO = false, hasX = false;
    for (int i = 0; i < r; ++ i){
        for (int j = 0; j < c; ++ j){
            if (!rtwo[i] && !ctwo[j]){
                if (s[i][j] == 'O'){
                    hasO = true;
                }
                else{
                    hasX = true;
                }
            }
        }
    }
    if (!hasO){
        for (int i = 0; i < r; ++ i){
            for (int j = 0; j < c; ++ j){
                if (s[i][j] != t[i][j]){
                    error();
                }
            }
        }
    }
    if (hasX) {
        hasX = false;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (!rtwo[i] && !ctwo[j]) {
                    if (t[i][j] == 'X') {
                        hasX = true;
                    }
                }
            }
        }
        if (!hasX){
            error();
        }
    }
    else{
        hasX = false;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (!rtwo[i] && !ctwo[j]) {
                    if (t[i][j] == 'X') {
                        hasX = true;
                    }
                }
            }
        }
        if (!hasX){
            for (int i = 0; i < r; ++ i){
                for (int j = 0; j < c; ++ j){
                    if (s[i][j] != t[i][j]){
                        error();
                    }
                }
            }
        }
    }
    puts("1");
    return 0;
}
