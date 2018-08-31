#include<bits/stdc++.h>

const int N = 100010;

int n;
int dx[N], dy[N];
int prex[N], prey[N];

int calc(int diffx, int diffy, std::vector <int> &vecx, int x1, int x2){
    int target = diffy - (diffy - diffx & 1);
    auto u = std::lower_bound(vecx.begin(), vecx.end(), x1);
    if (u != vecx.end() && *u < x2){
        return target - diffx;
    }
    int mindis = N;
    if (u != vecx.begin()){
        mindis = std::min(mindis, x1 - *-- u);
    }
    u = std::lower_bound(vecx.begin(), vecx.end(), x2);
    if (u != vecx.end()){
        mindis = std::min(mindis, *u - x2 + 1);
    }
    int diff = target - diffx;
    int one = std::max(diff - ((mindis - 1) << 1), 0);
    int five = diff - one;
    return one + 5 * five;
}

void solve(){
    std::vector <int> vecx, vecy;
    for (int i = 1; i < n; ++ i){
        scanf("%d", &dx[i]);
        if (dx[i] == 1){
            vecx.push_back(i);
        }
        prex[i] = prex[i - 1] + dx[i];
    }
    for (int i = 1; i < n; ++ i){
        scanf("%d", &dy[i]);
        if (dy[i] == 1){
            vecy.push_back(i);
        }
        prey[i] = prey[i - 1] + dy[i];
    }
    int q;
    scanf("%d", &q);
    while (q --){
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 > x2){
            std::swap(x1, x2);
        }
        if (y1 > y2){
            std::swap(y1, y2);
        }
        int ans = prex[x2 - 1] - prex[x1 - 1] + prey[y2 - 1] - prey[y1 - 1];
        int diffx = x2 - x1, diffy = y2 - y1;
        if (diffx <= diffy){
            ans += calc(diffx, diffy, vecx, x1, x2);
        }
        else{
            ans += calc(diffy, diffx, vecy, y1, y2);
        }
        printf("%d\n", ans);
    }
}

int main(){
    while (scanf("%d", &n) != EOF){
        solve();
    }
    return 0;
}
