#include <bits/stdc++.h>

struct P{
    int x, y;

    explicit P(int x = 0, int y = 0):x(x), y(y){}

    P operator +(const P &p)const{return P(x + p.x, y + p.y);}
    P operator -(const P &p)const{return P(x - p.x, y - p.y);}
    int operator ^(const P &p)const{return x * p.y - y * p.x;}
    int operator %(const P &p)const{return x * p.x + y * p.y;}
};

const int N = 20;

P p[N];

bool onRay(P p, P p1, P p2){
    return ((p2 - p) ^ (p1 - p)) == 0 && (p2 - p) % (p1 - p) > 0;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x;
            scanf("%d", &x);
            p[x] = P(i, j);
        }
    }
    int nowans = 1;
    P dir1 = p[2] - p[1], dir2(0, 0);
    bool real1 = false, real2 = false;
    for (int i = 3; i <= 16; ++ i){
        if (!dir2.x && !dir2.y){
            if (onRay(p[i - 1], p[i - 1] + dir1, p[i])){
                continue;
            }
            ++ nowans;
            dir1 = p[i] - p[i - 1];
            dir2 = p[i - 2] - p[i - 1];
            real1 = true, real2 = false;
            if ((dir1 ^ dir2) < 0) {
                std::swap(dir1, dir2);
                std::swap(real1, real2);
            }
            continue;
        }
        P dir = p[i] - p[i - 1];
        if (((dir1 ^ dir) > 0 && (dir ^ dir2) > 0) ||
            (real1 && onRay(p[i - 1], p[i - 1] + dir1, p[i])) ||
            (real2 && onRay(p[i - 1], p[i - 1] + dir2, p[i]))){
            dir1 = p[i] - p[i - 1];
            dir2 = P(0, 0);
            continue;
        }
        ++ nowans;
        if ((dir ^ dir2) >= 0 && !onRay(p[i - 1], p[i - 1] + dir2, p[i])){
            dir1 = P(0, 0) - dir1;
            real1 = false;
            dir2 = dir;
            real2 = true;
        }
        else if ((dir1 ^ dir) >= 0 && !onRay(p[i - 1], p[i - 1] + dir1, p[i])){
            dir1 = dir;
            real1 = true;
            dir2 = P(0, 0) - dir2;
            real2 = false;
        }
        else{
            dir1 = P(0, 0) - dir1;
            real1 = false;
            dir2 = P(0, 0) - dir2;
            real2 = false;
        }
    }
    printf("%d\n", nowans);
    return 0;
}
