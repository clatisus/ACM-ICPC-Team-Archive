#include<bits/stdc++.h>

struct KMP{
    #define MAXS (1000010)
    int n, m;
    int fail[MAXS];

    std::pair<int, int> getpos(char *s, char *t) {
        std::pair<int, int> ret = {-1, -1};
        m = strlen(s);
        fail[0] = -1;
        for(int i = 1, j = -1; i <= m; ++ i){
            while(j >= 0 && s[j] != s[i - 1]) j = fail[j];
            fail[i] = ++ j;
        }
        ret.first = m - fail[m];
        if (m % ret.first) ret.first = m;
        n = strlen(t);
        for(int i = 0, j = 0; i < n + n; ++ i){
            char ch = i < n ? t[i] : t[i - n];
            while(j >= 0 && s[j] != ch) j = fail[j];
            if(++ j == m){
                ret.second = i - m + 1;
                break;
            }
        }
        for (int i = 1; i <= m; ++i) fail[i] = 0;
        return ret;
    }
    #undef MAXS
}kmp;

int ex_euc(int a, int b, int &x, int &y){
    if (!b){
        x = 1, y = 0;
        return a;
    }
    int ret = ex_euc(b, a % b, x, y), tmp = y;
    y = x - a / b * y;
    x = tmp;
    return ret;
}

struct modequa{
    int remain, moder;

    modequa crt(const modequa &p)const{
        modequa p1 = *this, p2 = p;
        if (p1.moder < p2.moder) std::swap(p1, p2);
        int x, y;
        int gcd = ex_euc(p1.moder, p2.moder, x, y);
        if ((p2.remain - p1.remain) % gcd) return {0, 0};
        int lcm = p1.moder / gcd * p2.moder;
        int ans = (p2.remain - p1.remain) / gcd;
        ans = 1ll * ans * x % (p2.moder / gcd) * p1.moder;
        ans += p1.remain;
        ans += ans < 0 ? lcm : ans >= lcm ? -lcm : 0;
        return {ans, lcm};
    }
};

const int N = 1000010;

int p[N];
bool vis[N];
char s[N], t[N];
char tmp1[N], tmp2[N];

int main(){
    scanf("%s%s", s + 1, t + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n >> 1; ++ i){
        p[i] = (i << 1) - 1;
        p[i + (n >> 1)] = i << 1;
    }
    modequa md = {0, 1};
    for (int i = 1; i <= n; ++ i){
        if (vis[i]) continue;
        int x = i;
        int cnt = 0;
        while (true){
            tmp1[cnt] = s[x];
            tmp2[cnt ++] = t[x];
            vis[x] = true;
            x = p[x];
            if (x == i){
                break;
            }
        }
        tmp1[cnt] = tmp2[cnt] = 0;
        //printf("s = %s, t = %s\n", tmp1, tmp2);
        std::pair <int, int> pp = kmp.getpos(tmp2, tmp1);
        //printf("%d %d\n", pp.first, pp.second);
        if (pp.second == -1){
            puts("-1");
            return 0;
        }
        md = md.crt({pp.second % pp.first, pp.first});
        if (md.moder == 0){
            puts("-1");
            return 0;
        }
    }
    printf("%d\n", md.remain);
    return 0;
}
