#include<bits/stdc++.h>

const double eps = 1e-9;
const double PI = std::acos(-1.0);
const double INF = 1e100;

inline int sig(double p){return (p > eps) - (p < -eps);}

const int N = 10;

char s[N];

int solve(){
    double angle, l;
    scanf("%s%lf%lf", s, &angle, &l);
    angle = angle * PI / 180;
    if (s[0] == 'B'){
        angle = 5 * PI / 3 - angle;
    }
    else if (s[0] == 'C'){
        angle = 4 * PI / 3 - angle;
    }
    else{
        angle = 2 * PI - angle;
    }
    double x = std::cos(angle) * l;
    double y = std::sin(angle) * l;
    double sqrt3 = std::sqrt(3);
    while (y < -sqrt3){
        x += 1;
        y += sqrt3;
    }
    x += 1;
    y += sqrt3;
    double ny = y * 2 / sqrt3;
    double nx = x - ny * 0.5;
    while (nx < 0){
        nx += 2;
    }
    while (nx > 2){
        nx -= 2;
    }
    if (nx < 1 && ny < 1){
        if (nx + ny < 1){
            return 2;
        }
        else{
            return 1;
        }
    }
    if (1 < nx && nx < 2 && ny < 1){
        if (nx - 1 + ny < 1){
            return 3;
        }
        else{
            return 4;
        }
    }
    if (nx < 1 && 1 < ny && ny < 2){
        if (nx + ny - 1 < 1){
            return 4;
        }
        else{
            return 3;
        }
    }
    if (1 < nx && nx < 2 && 1 < ny && ny < 2){
        if (nx - 1 + ny - 1 < 1){
            return 1;
        }
        else{
            return 2;
        }
    }
    return -1;
}

int main(){
    int x1 = solve();
    int x2 = solve();
    puts(x1 == x2 ? "YES" : "NO");
    return 0;
}

