#include "testlib.h"
#include<bits/stdc++.h>

typedef long long ll;
const int MAXT = 1000;
const int MAXN = 5000;
const int SMALLN = 100;
const int BIGNCNT = 3;
const int MAXSIGMA = 5000;
const ll MAXK = 1'000'000'000'000'000'000;

int main(int argc, char **argv){
    registerValidation(argc, argv);
    int T = inf.readInt(1, MAXT, "T");
    inf.readEoln();
    int bign = 0;
    while (T --){
        int n = inf.readInt(1, MAXN, "n");
        bign += n > SMALLN;
        inf.readSpace();
        int sigma = inf.readInt(1, MAXSIGMA, "sigma");
        inf.readSpace();
        ll k = inf.readLong(1, MAXK, "k");
        ensure(n > 60 || k <= (1ll << n) - 1);
        inf.readEoln();
        inf.readInts(n, 1, sigma);
        inf.readEoln();
    }
    ensure(bign <= BIGNCNT);
    inf.readEof();
    return 0;
}
