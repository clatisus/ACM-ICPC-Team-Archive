#include <bits/stdc++.h>

typedef long long ll;
typedef std::pair <int, int> pii;
const int N = 1010;
const int BIT = 13;

ll loop = 1, res = LLONG_MAX;
pii word;
char s[N];
pii p[N];
int wcnt, vcnt, wid;
int b, ss;
ll preans[N][N], totans;
int zerobit;
int lb[1 << BIT];

void getword(){
    if (wid == wcnt){
        word = {-1, -1};
        return;
    }
    if (p[wid].first == 0){
        word = p[wid ++];
        return;
    }
    if (p[wid].first == 1){
        int x = p[wid ++].second;
        word = {1, zerobit >> x & 1 ? -1 : x};
        return;
    }
    word = p[wid ++];
}

pii getloop(int x);

pii getprogram(){
    pii p;
    if (word.first == 0){
        int x = word.second;
        loop *= x;
        getword();
        p = getloop(x);
        if (p.first >= 0 && p.second >= 0 && p.first != p.second){
            preans[p.first][p.second] += loop * (x - 1);
            preans[p.second][p.first] += loop * (x - 1);
        }
        getword();
    }
    else if (word.first == 1){
        p = {word.second, word.second};
        totans += loop;
        getword();
    }
    else{
        return {-2, -2};
    }
    pii q = getprogram();
    if (q.first == -2){
        return p;
    }
    if (p.first == -1){
        return q;
    }
    if (q.first == -1){
        return p;
    }
    if (p.second != q.first){
        preans[p.second][q.first] += loop;
        preans[q.first][p.second] += loop;
    }
    return {p.first, q.second};
}

pii getloop(int x){
    pii ret = getprogram();
    loop /= x;
    return ret;
}

void dfs(int now, int bit, int pre, ll nowans){
    if (now == b || bit == (1 << vcnt) - 1){
        if (bit != (1 << vcnt) - 1){
            return;
        }
        res = std::min(res, nowans + (zerobit != bit));
        return;
    }
    if (now == 0){
        int bits = std::min(ss, vcnt);
        for (int i = 0; i < 1 << vcnt; ++ i){
            if (__builtin_popcount(i) != bits){
                continue;
            }
            memset(preans, 0, sizeof(preans));
            wid = totans = 0;
            zerobit = i;
            getword();
            getprogram();
            dfs(1, i, 0x3f3f3f3f, 0);
        }
        return;
    }
    int minbit = 0;
    for (int i = 0; i < vcnt; ++ i){
        if (!(bit >> i & 1)){
            minbit = i;
            break;
        }
    }
    for (int begin = ((1 << vcnt) - 1) ^ bit, i = begin; i; i = (i - 1) & begin){
        if (!(i >> minbit & 1)){
            continue;
        }
        if (__builtin_popcount(i) > ss){
            continue;
        }
        if (pre + __builtin_popcount(i) <= ss){
            continue;
        }
        ll newans = nowans;
        for (int j = i; j; j -= j & -j){
            for (int k = bit ^ zerobit; k; k -= k & -k){
                newans += preans[lb[j & -j]][lb[k & -k]];
            }
        }
        dfs(now + 1, bit | i, std::min(pre, __builtin_popcount(i)), newans);
    }
}

int main(){
    for (int i = 0; i < BIT; ++ i){
        lb[1 << i] = i;
    }
    scanf("%d%d", &b, &ss);
    std::map <int, int> map;
    while (scanf("%s", s) != EOF){
        if (s[0] == 'R'){
            int time;
            sscanf(s + 1, "%d", &time);
            p[wcnt ++] = {0, time};
        }
        else if (s[0] == 'V'){
            int id;
            sscanf(s + 1, "%d", &id);
            int x = map.size();
            id = map.count(id) ? map[id] : map[id] = x;
            vcnt = std::max(vcnt, id + 1);
            p[wcnt ++] = {1, id};
        }
        else{
            p[wcnt ++] = {2, 0};
        }
    }
    dfs(0, 0, 0, 0);
    printf("%lld\n", res + totans);
    return 0;
}
