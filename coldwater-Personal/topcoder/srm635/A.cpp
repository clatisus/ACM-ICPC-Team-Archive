#include <bits/stdc++.h>

#define ll long long
#define MAXN (410)

class SimilarRatingGraph
{
    ll x[MAXN];
    ll y[MAXN];
    double len[MAXN];
public:
    double maxLength(std::vector<int> date, std::vector<int> rating) {
        int n = (int)(date.size());
        for (int i = 0; i < n - 1; ++ i) {
            x[i] = date[i + 1] - date[i];
            y[i] = rating[i + 1] - rating[i];
            len[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
        }
        -- n;
        double ans = 0.0;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (i == j) continue;
                // y[j] / y[i] == x[j] / x[i]
                double now = 0.0;
                for (int k = 0; k + i < n && k + j < n; ++ k) {
                    if (x[j + k] * x[i] != x[j] * x[i + k]) break;
                    if (y[j + k] * x[i] != x[j] * y[i + k]) break;
                    now += len[i + k];
                }
                if (now > ans) {
                    ans = now;
                }
            }
        }
        return ans;
    }
};

int main()
{
    SimilarRatingGraph run;
    printf("%.10lf\n", run.maxLength(
                {1, 2, 4, 8, 16, 32},
                {1, 2, 4, 8, 16, 32}
            )
          );
    return 0;
}
