#include<bits/stdc++.h>

const double PI = std::acos(-1.0);

struct poly{
    static const int N = 20;

    double a[N];

    poly (){memset(a, 0, sizeof(a));}

    double value(double x){
        double ret = 0, now = 1;
        for (int i = 0; i < N; ++ i){
            ret += now * a[i];
            now *= x;
        }
        return ret;
    }

    poly integral(){
        poly ret;
        for (int i = 0; i < N - 1; ++ i){
            ret.a[i + 1] = a[i] / (i + 1);
        }
        return ret;
    }

    double integral(double a, double b){
        return integral().value(b) - integral().value(a);
    }

    poly sqr(){
        poly ret;
        for (int i = 0; i < N; ++ i){
            for (int j = 0; i + j < N; ++ j){
                ret.a[i + j] += a[i] * a[j];
            }
        }
        return ret;
    }
};

double solve(){
    int n;
    scanf("%d", &n);
    poly pp;
    for (int i = n; i >= 0; -- i){
        scanf("%lf", &pp.a[i]);
    }
    poly p = pp.sqr();
    double a, b;
    int slices, stacks;
    scanf("%lf%lf%d%d", &a, &b, &slices, &stacks);
    double tvalue = p.integral(a, b) * PI, avalue = 0;
    double diff = (b - a) / stacks;
    double area = slices / 2.0 * std::sin(2 * PI / slices);
    for (int i = 0; i < stacks; ++ i){
        poly q;
        double x1 = a + diff * i, x2 = a + diff * (i + 1);
        q.a[1] = (pp.value(x2) - pp.value(x1)) / (x2 - x1);
        //printf("x1 = %f, x2 = %f, y1 = %f, y2 = %f, k = %f\n", x1, x2, pp.value(x1), pp.value(x2), q.a[2]);
        q.a[0] = pp.value(x2) - q.a[1] * x2;
        avalue += q.sqr().integral(x1, x2) * area;
    }
    return std::abs(tvalue - avalue) / tvalue * 100;
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case %d: %.4f\n", i, solve());
    }
    return 0;
}

