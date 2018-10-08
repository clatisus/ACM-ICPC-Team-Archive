#include<bits/stdc++.h>

typedef long long ll;
const int N = 100010;
const int INF = 61;

char ans[N], oddans[N], evenans[N];
int odddone, evendone, odd, even;
int n;
bool oddtrue, eventrue;

int count(char *ans, char ch, int cnt, int done, bool valid){
    if (!valid){
        return -1;
    }
    if (done >= (cnt + 1) >> 1){
        if (ch != ans[cnt - done]){
            return -1;
        }
    }
    return (std::max(0, cnt - (done + 1) * 2) + 1) >> 1;
}

int count2(int cnt, int done, bool valid){
    if (!valid){
        return -1;
    }
    return (std::max(0, cnt - done * 2) + 1) >> 1;
}

bool update(char *ans, char ch, int &done, int cnt){
    ans[++ done] = ch;
    if (done > (cnt + 1) >> 1){
        return ch == ans[cnt - done + 1];
    }
    return true;
}

ll calc(int x){
    return x == -1 ? 0 : 1ll << x;
}

void solve(){
    ll k;
    scanf("%d%lld", &n, &k);
    odddone = 0, evendone = 0;
    odd = (n + 1) >> 1, even = n >> 1;
    oddtrue = true;
    eventrue = true;
    for (int i = n; i >= 1; -- i){
        if (i & 1){
            int cnt1 = count(oddans, '0', odd, odddone, oddtrue);
            int cnt2 = count2(even, evendone, eventrue);
            int cnt3 = cnt1 == -1 || cnt2 == -1 ? -1 : cnt1 + cnt2;
            if (cnt1 != -1) cnt1 += even - evendone;
            if (cnt2 != -1) cnt2 += odd - odddone - 1;
            if (cnt1 >= INF || cnt2 >= INF){
                bool tmp = update(oddans, '0', odddone, odd);
                oddtrue = oddtrue && tmp;
                ans[i] = '0';
                continue;
            }
            ll tot = calc(cnt1) + calc(cnt2) - calc(cnt3);
            if (tot >= k){
                bool tmp = update(oddans, '0', odddone, odd);
                oddtrue = oddtrue && tmp;
                ans[i] = '0';
                continue;
            }
            k -= tot;
            bool tmp = update(oddans, '1', odddone, odd);
            oddtrue = oddtrue && tmp;
            ans[i] = '1';
            continue;
        }
        else{
            int cnt1 = count(evenans, '0', even, evendone, eventrue);
            int cnt2 = count2(odd, odddone, oddtrue);
            int cnt3 = cnt1 == -1 || cnt2 == -1 ? -1 : cnt1 + cnt2;
            if (cnt1 != -1) cnt1 += odd - odddone;
            if (cnt2 != -1) cnt2 += even - evendone - 1;
            if (cnt1 >= INF || cnt2 >= INF){
                bool tmp = update(evenans, '0', evendone, even);
                eventrue = eventrue && tmp;
                ans[i] = '0';
                continue;
            }
            ll tot = calc(cnt1) + calc(cnt2) - calc(cnt3);
            if (tot >= k){
                bool tmp = update(evenans, '0', evendone, even);
                eventrue = eventrue && tmp;
                ans[i] = '0';
                continue;
            }
            k -= tot;
            bool tmp = update(evenans, '1', evendone, even);
            eventrue = eventrue && tmp;
            ans[i] = '1';
            continue;
        }
    }
    if (k > 1){
        puts("NOT FOUND!");
        return;
    }
    std::reverse(ans + 1, n + ans + 1);
    ans[n + 1] = '\0';
    puts(ans + 1);
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}

