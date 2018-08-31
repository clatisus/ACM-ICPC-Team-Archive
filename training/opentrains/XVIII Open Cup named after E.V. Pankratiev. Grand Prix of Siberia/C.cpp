#include<bits/stdc++.h>
#define mp std::make_pair

typedef long long ll;
typedef std::pair <int, int> pii;

const int N = 1010;
const int P = 1680;

struct Mirror{
    int r, c, a, t, p;

    void read(){
        scanf("%d%d%d%d%d", &r, &c, &a, &t, &p);
    }
};

void changedir(int &dir, int a){
    //dir: 0 -> left, 1 -> up, 2 -> right, 3 -> down
    if (a == 0){
        if (dir % 2 == 0){
            dir = 2 - dir;
        }
    }
    else if (a == 1){
        dir = 3 - dir;
    }
    else if (a == 2){
        if (dir & 1){
            dir = 4 - dir;
        }
    }
    else{
        dir = dir ^ 1;
    }
}

ll dp[N][P + 10][4];
bool vis[N][P + 10][4];
int r[N], c[N];
Mirror mir[N];
std::map <int, std::vector <int>> mapr, mapc;
int n, m, r0, c0;
std::map <pii, int> Hash;

int nextp(int &r, int &c, int &dir){
    if (dir == 0){
        if (!mapr.count(r)){
            return -1;
        }
        auto &u = mapr[r];
        auto v = std::lower_bound(u.begin(), u.end(), c);
        if (v == u.begin()){
            int newc = u.front();
            int ret = c - 1 + newc - 1 + 1;
            dir ^= 2;
            c = newc;
            return ret;
        }
        int newc = *(-- v);
        int ret = c - newc;
        c = newc;
        return ret;
    }
    if (dir == 1){
        if (!mapc.count(c)){
            return -1;
        }
        auto &u = mapc[c];
        auto v = std::lower_bound(u.begin(), u.end(), r);
        if (v == u.begin()){
            int newr = u.front();
            int ret = r - 1 + newr - 1 + 1;
            dir ^= 2;
            r = newr;
            return ret;
        }
        int newr = *(-- v);
        int ret = r - newr;
        r = newr;
        return ret;
    }
    if (dir == 2){
        if (!mapr.count(r)){
            return -1;
        }
        auto &u = mapr[r];
        auto v = std::upper_bound(u.begin(), u.end(), c);
        if (v == u.end()){
            int newc = u.back();
            int ret = m - c + m - newc + 1;
            dir ^= 2;
            c = newc;
            return ret;
        }
        int newc = *v;
        int ret = newc - c;
        c = newc;
        return ret;
    }
    if (dir == 3){
        if (!mapc.count(c)){
            return -1;
        }
        auto &u = mapc[c];
        auto v = std::upper_bound(u.begin(), u.end(), r);
        if (v == u.end()){
            int newr = u.back();
            int ret = n - r + n - newr + 1;
            dir ^= 2;
            r = newr;
            return ret;
        }
        int newr = *v;
        int ret = newr - r;
        r = newr;
        return ret;
    }
    return -1;
}

ll solve(int sit, int dir, int time){
    int r = mir[sit].r, c = mir[sit].c;
    if (vis[sit][time][dir]){
        return dp[sit][time][dir];
    }
    vis[sit][time][dir] = true;
    int ndir = dir;
    int dis = nextp(r, c, ndir);
    if (dis == -1){
        return dp[sit][time][dir] = -1;
    }
    if (r == r0 && c == c0){
        return dp[sit][time][dir] = dis;
    }
    int ntime = (time + dis) % P;
    int nsit = Hash[mp(r, c)];
    int a = ((mir[nsit].t == -1 ? 0 : ntime / mir[nsit].p + (ntime % mir[nsit].p >= mir[nsit].t)) + mir[nsit].a) & 3;
    changedir(ndir, a);
    ll ans = solve(nsit, ndir, ntime);
    if (ans == -1){
        return dp[sit][time][dir] = -1;
    }
    return dp[sit][time][dir] = dis + ans;
}

int main(){
    int k, s;
    scanf("%d%d%d%d%d%d", &n, &m, &k, &s, &r0, &c0);
    mapr[r0].push_back(c0);
    mapc[c0].push_back(r0);
    for (int i = 0; i < k; ++ i){
        scanf("%d%d", &r[i], &c[i]);
    }
    for (int i = 0; i < s; ++ i){
        mir[i].read();
        mapr[mir[i].r].push_back(mir[i].c);
        mapc[mir[i].c].push_back(mir[i].r);
        Hash[mp(mir[i].r, mir[i].c)] = i;
    }
    for (auto &u : mapr){
        std::sort(u.second.begin(), u.second.end());
    }
    for (auto &u : mapc){
        std::sort(u.second.begin(), u.second.end());
    }
    memset(dp, -1, sizeof(dp));
    ll min = -1;
    for (int ii = 0; ii < P; ++ ii){
        for (int i = 0; i < k; ++ i){
            for (int j = 0; j < 4; ++ j){
                int time = ii, dir = j;
                int r = ::r[i], c = ::c[i];
                ll dis = nextp(r, c, dir);
                if (dis == -1){
                    continue;
                }
                ll ans = dis + time;
                if (r == r0 && c == c0){
                    if (min == -1 || min > ans){
                        min = ans;
                    }
                    continue;
                }
                int ntime = (time + dis) % P;
                int nsit = Hash[mp(r, c)];
                int a = ((mir[nsit].t == -1 ? 0 : ntime / mir[nsit].p + (ntime % mir[nsit].p >= mir[nsit].t)) + mir[nsit].a) & 3;
                changedir(dir, a);
                dis = solve(nsit, dir, ntime);
                if (dis == -1){
                    continue;
                }
                ans += dis;
                if (min == -1 || min > ans){
                    min = ans;
                }
            }
        }
    }
    printf("%lld\n", min);
    return 0;
}
