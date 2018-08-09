#include<bits/stdc++.h>
 
struct bitset{
    std::vector <unsigned> vec;
 
    bitset():vec(std::vector <unsigned>()){}
    bitset(int sz):vec(std::vector <unsigned>(sz)){}
 
    bitset operator & (const bitset &s)const{
        bitset ret(vec.size());
        for (int i = 0; i < vec.size(); ++ i){
            ret.vec[i] = vec[i] & s.vec[i];
        }
        return ret;
    }
 
    bitset operator | (const bitset &s)const{
        bitset ret(vec.size());
        for (int i = 0; i < vec.size(); ++ i){
            ret.vec[i] = vec[i] | s.vec[i];
        }
        return ret;
    }
 
    bitset operator ^ (const bitset &s)const{
        bitset ret(vec.size());
        for (int i = 0; i < vec.size(); ++ i){
            ret.vec[i] = vec[i] ^ s.vec[i];
        }
        return ret;
    }
};
 
typedef long long ll;
const int N = 4;
const int M = 5000000;
 
ll dp[N + 2][1 << (1 << N)];
std::vector <bitset> set[2];
char s[M];
 
int main(){
    int n;
    scanf("%d%s", &n, s);
    /*n = 18;
    for (int i = 0; i < 1 << n; ++ i){
        s[i] = '1';
    }*/
    int nn = 1 << n;
    for (int i = 1, j = 0; i < nn - 1; ++ i){
        for (int s = nn; j ^= s >>= 1, ~j & s; )
            ;
        if (i < j){
            std::swap(::s[i], ::s[j]);
        }
    }
    if (n > 4){
        int now = 0;
        bitset sset(1 << n - 5);
        for (int i = 0; i < 1 << n; i += 32){
            unsigned x = 0;
            for (int j = 0; j < 32; ++ j){
                x |= s[i + j] - '0' << j;
            }
            sset.vec[i >> 5] = x;
        }
        set[now].push_back(sset);
        while (n > 4){
            if (n == 5){
                for (auto &u : set[now]){
                    unsigned x = u.vec[0] >> 16;
                    unsigned y = u.vec[0] & ((1 << 16) - 1);
                    ++ dp[4][x & y];
                    ++ dp[4][x | y];
                    ++ dp[4][x ^ y];
                }
            }
            else{
                std::vector <bitset>().swap(set[now ^ 1]);
                for (auto &u : set[now]){
                    int sz = u.vec.size() >> 1;
                    bitset setx(sz);
                    bitset sety(sz);
                    for (int i = 0; i < sz; ++ i){
                        setx.vec[i] = u.vec[i];
                        sety.vec[i] = u.vec[i + sz];
                    }
                    set[now ^ 1].push_back(setx & sety);
                    set[now ^ 1].push_back(setx | sety);
                    set[now ^ 1].push_back(setx ^ sety);
                }
            }
            -- n;
            now ^= 1;
        }
    }
    else{
        int x = 0;
        for (int i = 0; i < 1 << n; ++ i){
            x |= s[i] - '0' << i;
        }
        dp[n][x] = 1;
    }
    for (int i = n; i >= 1; -- i){
        for (int j = 0; j < 1 << (1 << i); ++ j){
            unsigned x = j >> (1 << i - 1);
            unsigned y = j & ((1 << (1 << i - 1)) - 1);
            dp[i - 1][x & y] += dp[i][j];
            dp[i - 1][x | y] += dp[i][j];
            dp[i - 1][x ^ y] += dp[i][j];
        }
    }
    printf("%lld\n", dp[0][1]);
    return 0;
}
