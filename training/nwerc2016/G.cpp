#include<bits/stdc++.h>

const int N = 1000010;
const int T = 1800;
typedef long long ll;
typedef std::pair <int, int> pii;
inline ll lowbit(ll n){return n & -n;}

struct pokemon{
    int time;
    pii id;

    bool operator < (const pokemon &p)const{
        return time < p.time;
    }
};

struct fenwick{
    std::vector <ll> c;
    ll tot = 0;

    fenwick(){}
    fenwick(int sz){c.resize(sz);}

    void add(int sit, ll value){
        tot += value;
        for (++ sit; sit < c.size(); sit += lowbit(sit)){
            c[sit] += value;
        }
    }

    ll query(int sit){
        ll ret = 0;
        for (++ sit; sit; sit -= lowbit(sit)){
            ret += c[sit];
        }
        return ret;
    }

    ll all(){
        return tot;
    }
};

std::map <std::string, pii> nameHash;
std::vector <ll> vec[N];
fenwick c[N];
char s[N];
pokemon p[N];
ll xp[N];

int main(){
    int f;
    scanf("%d", &f);
    for (int i = 0, n; i < f; ++ i){
        scanf("%d", &n);
        vec[i].push_back(0);
        for (int j = 0, cost; j < n - 1; ++ j){
            scanf("%s%d", s, &cost);
            nameHash[s] = {i, j};
            vec[i].push_back(vec[i].back() + cost);
        }
        scanf("%s", s);
        nameHash[s] = {i, n - 1};
        c[i] = c[i + f] = c[i + 2 * f] = fenwick(n + 10);
    }
    int n;
    scanf("%d", &n);
    for (int i = 0, t; i < n; ++ i){
        scanf("%d%s", &t, s);
        p[i] = {t, nameHash[s]};
    }
    ll nowxp = n * 100, maxxp = 0, sum = 0;
    std::queue <pokemon> q;
    for (int i = 0; i < n; ++ i){
        while (!q.empty() && p[i].time - q.front().time >= T){
            q.pop();
            nowxp -= 100;
        }
        q.push(p[i]);
        nowxp += 100;
        pii id = p[i].id;
        c[id.first].add(id.second, 1);
        c[id.first + f].add(id.second, vec[id.first][id.second]);
        c[id.first + 2 * f].add(id.second, id.second);
        int left = 0, right = vec[id.first].size() - 1;
        int tot = 4 * c[id.first].all() - 1;
        while (left < right){
            int mid = left + right + 1 >> 1;
            int num = c[id.first].query(mid);
            if (num * vec[id.first][mid] - c[id.first + f].query(mid) > tot){
                right = mid - 1;
            }
            else{
                left = mid;
            }
        }
        sum -= xp[id.first];
        int num = c[id.first].query(left);
        tot -= num * vec[id.first][left] - c[id.first + f].query(left);
        xp[id.first] = (1ll * num * left - c[id.first + 2 * f].query(left)) * 1000;
        if (left < vec[id.first].size() - 1){
            xp[id.first] += std::min((ll) num, tot / (vec[id.first][left + 1] - vec[id.first][left])) * 1000;
        }
        sum += xp[id.first];
        maxxp = std::max(maxxp, nowxp + sum);
    }
    printf("%lld\n", maxxp);
    return 0;
}
