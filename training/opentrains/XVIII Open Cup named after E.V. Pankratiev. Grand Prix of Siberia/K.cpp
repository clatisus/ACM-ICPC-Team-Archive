#include<bits/stdc++.h>

const long double eps = 1e-12;

inline int sig(long double x){return (x > eps) - (x < -eps);}

int getcross(long double k, long double b, long double d){
    int signal = sig(b + 1 - d + std::log(k));
    if (signal == -1){
        return 2;
    }
    if (signal == 0){
        return 1;
    }
    return 0;
}

long double getpt(long double k, long double b, long double d){
    long double left = 1 / k, right = 200;
    for (int i = 0; i < 60; ++ i){
        long double mid = (left + right) / 2;
        if (k * mid + b < std::log(mid) + d){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    return left;
}

void solve(){
    int n, c;
    long double a, b;
    scanf("%d%d%Lf%Lf", &n, &c, &a, &b);
    long double left = 0, right = 10;
    for (int i = 0; i < 60; ++ i){
        long double mid = (left + right) / 2;
        long double beginx = a, beginy = std::log(a) + mid;
        long double endx = b, endy = std::log(b) + mid;
        int cnt = 0;
        long double nowx = beginx, nowy = beginy;
        while (cnt <= n){
            //printf("nowx = %.10Lf, nowy = %.10Lf\n", nowx, nowy);
            if (sig(nowx - endx) >= 0) break;
            long double k = (endy - nowy) / (endx - nowx);
            long double b = nowy - nowx * k;
            if (getcross(k, b, -mid) <= 1){
                ++ cnt;
                break;
            }
            long double lleft = nowx, rright = endx;
            for (int i = 0; i < 200; ++ i){
                long double mmid = (lleft + rright) / 2;
                long double yy = std::log(mmid) + mid; 
                long double k = (yy - nowy) / (mmid - nowx);
                long double b = nowy - nowx * k;
                if (getcross(k, b, -mid) <= 1){
                    lleft = mmid;
                }
                else{
                    rright = mmid;
                }
            }
            nowx = lleft;
            nowy = std::log(nowx) + mid;
            ++ cnt;
        }
        //printf("------------------\n");
        if (cnt > n){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    printf("%.10Lf\n", left * c);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}
