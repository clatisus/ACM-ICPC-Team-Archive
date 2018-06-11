#include<bits/stdc++.h>

const int N = 50010;

struct connect{
    static const int N = 10;
    static int index;
    static int type;

    int low[N], high[N];
    int sz;

    connect():sz(1){}

    bool operator < (const connect &c)const{
        if (!type){
            return low[index] < c.low[index];
        }
        else{
            return high[index] < c.high[index];
        }
    }
};

int connect::index = 0;
int connect::type = 0;

connect c[N];

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    std::set <connect> set;
    for (int i = 0; i < n; ++ i){
        connect newcon;
        for (int j = 0, x; j < k; ++ j){
            scanf("%d", &x);
            newcon.low[j] = newcon.high[j] = x;
        }
        auto minit = set.end(), maxit = set.begin();
        auto max = [](auto set, auto it1, auto it2){
            if (it1 == set.end() || it2 == set.end()) return set.end();
            return it1 -> low[0] > it2 -> low[0] ? it1 : it2;
        };
        auto min = [](auto set, auto it1, auto it2){
            if (it1 == set.end()) return it2;
            if (it2 == set.end()) return it1;
            return it1 -> low[0] > it2 -> low[0] ? it2 : it1;
        };
        for (int j = 0; j < k; ++ j){
            connect::index = j;
            connect::type = 1;
            minit = min(set, minit, set.lower_bound(newcon));
            connect::type = 0;
            maxit = max(set, maxit, set.lower_bound(newcon));
        }
        if (minit == maxit){
            set.insert(newcon);
        }
        else{
            for (auto u = minit; u != maxit; ++ u){    
                for (int j = 0; j < k; ++ j){
                    newcon.low[j] = std::min(newcon.low[j], u -> low[j]);
                    newcon.high[j] = std::max(newcon.high[j], u -> high[j]);
                }
                newcon.sz += u -> sz;
            }
            set.erase(minit, maxit);
            set.insert(newcon);
        }
        printf("%d\n", (-- set.end()) -> sz);
    }
    return 0;
}
