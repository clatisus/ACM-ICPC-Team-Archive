#include<bits/stdc++.h>

const int N = 1 << 20;
const int M = 7;
typedef std::pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;

int bitcnt[N], gen[N][M];
ull bits[N][M];
int money = 160;
int seed = 4168;

bool ask(int x){
    printf("%d\n", x);
    fflush(stdout);
    int tmp;
    //scanf("%d", &tmp);
    tmp = money + (bitcnt[seed] ? x : -x);
    if (tmp == 200) tmp = -1;
    seed = gen[seed][0];
    if (tmp == -1){
        exit(0);
    }
    bool ret = tmp == money + x;
    money = tmp;
    return ret;
}

int main(){
    for (int i = 1; i < N; ++ i){
        bitcnt[i] = bitcnt[i >> 1] ^ (i & 1);
    }
    for (int i = 0; i < N; ++ i){
        gen[i][0] = ((487237ll * i + 1011807) & 0xfffff);
    }
    for (int i = 1; i < M; ++ i){
        for (int j = 0; j < N; ++ j){
            gen[j][i] = gen[gen[j][i - 1]][i - 1];
        }
    }
    for (int i = 0; i < N; ++ i){
        bits[i][0] |= bitcnt[gen[i][0]];
    }
    for (int i = 1; i < M; ++ i){
        for (int j = 0; j < N; ++ j){
            bits[j][i] = bits[gen[j][i - 1]][i - 1] << (1 << (i - 1)) | bits[j][i - 1];
        }
    }
    /*
    std::vector <ull> vec;
    for (int i = 0; i < N; ++ i){
        vec.push_back(bits[i][6]);
    }
    std::sort(vec.begin(), vec.end());
    for (int i = 0, sz = vec.size(); i < sz - 1; ++ i){
        assert(vec[i] != vec[i + 1]);
    }
    */
    ull mask = 0;
    ask(1);
    for (int i = 0; i < 64; ++ i){
        mask |= (ull) ask(1) << i;
    }
    int x;
    for (int i = 0; i < N; ++ i){
        if (mask == bits[i][6]){
            x = i;
            break;
        }
    }
    //printf("%d\n", x);
    while (true){
        if (bitcnt[x]){
            ask(std::min(money, 200 - money));
        }
        else{
            ask(1);
        }
        x = gen[x][0];
    }
    return 0;
}
