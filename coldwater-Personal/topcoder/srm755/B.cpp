#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class OneHandRoadPainting {
public:
    long long fastest(vector <int> dStart, vector <int> dEnd, int paintPerBrush) {
        ll ans = 0;
        ll now = 0;
        for (int i = dStart.size() - 1; ~i; --i) {
            ll s = dStart[i], e = dEnd[i];
            if (now >= e - s) {
                now -= e - s;
                continue;
            }
            e -= now;
            now = 0;
            ll d = (e - s) / paintPerBrush;
            ll m = (e - s) % paintPerBrush;

            ans += (s + m) * d + d * (d + 1) / 2 * paintPerBrush;
            if (m) {
                ans += s + m;
                now = paintPerBrush - m;
            }
        }

        return ans << 1;
    }
};
