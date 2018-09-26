// bsgs模板
// 求方程 a^x = b(mod moder) 的最小正解，无解时返回-1
// solve() 返回解

#include<bits/stdc++.h>
#include"euclidinv.cpp"

typedef long long ll;

class bsgs{
private:
    static std::vector <std::pair <int, int>> vec;
    
    int ans;
    
    static int powermod(int a, int exp, int moder){
        int ret = 1;
        for ( ; exp; exp >>= 1){
            if (exp & 1){
                ret = 1ll * ret * a % moder;
            }
            a = 1ll * a * a % moder;
        }
        return ret;
    }
    
    // moder 为质数时可直接使用 
    int BSGS(int a, int b, int moder){
        a = (a % moder + moder) % moder;
        b = (b % moder + moder) % moder;
        if (!a && !b) return 0;
        if (!a || !b) return -1;
        vec.clear();
        int now = b, x = a, m = std::sqrt(moder) + 1;
        for (int i = 0; i < m; ++ i, now = 1ll * now * x % moder){
            vec.push_back({now, -i});
        }
        std::sort(vec.begin(), vec.end());
        x = now = powermod(a, m, moder);
        for (int i = 1; i <= m; ++ i, now = 1ll * now * x % moder){
            auto v = std::lower_bound(vec.begin(), vec.end(), std::make_pair(now, -INT_MAX));
            if (v != vec.end() && v -> first == now) return i * m + v -> second;
        }
        return -1;
    }
    
    int Bsgs(int a, int b, int moder){
        int cnt = 0;
        for (int gcd; (gcd = std::__gcd(a, moder)) != 1; ++ cnt){
            if (b % gcd) return -1;
            moder /= gcd;
            b = 1ll * b / gcd * inv <int>(a / gcd, moder) % moder;
            if (b == 1)    return cnt + 1;
        }
        int ret = BSGS(a, b, moder);
        return !~ret ? -1 : ret + cnt;
    }
    
public:
    bsgs(){}
    
    bsgs(int a, int b, int moder){
        ans = Bsgs(a, b, moder);
    }
    
    int solve(){
        return ans;
    }
};

std::vector <std::pair <int, int>> bsgs::vec;

int main(){
    return 0;
}
