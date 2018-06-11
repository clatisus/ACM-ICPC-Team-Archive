#include <bits/stdc++.h>

class ORSolitaire
{
public:
    int getMinimum(std::vector<int> numbers, int goal) {
        std::vector<int> vec;
        for (auto v : numbers) {
            if (!(v & ~goal)) {
                vec.push_back(v);
            }
        }
        int ans = (int)(vec.size());
        for (int i = 0; i < 31; ++ i) {
            if (!((goal >> i) & 1)) continue;
            int now = 0;
            for (auto v : vec) {
                now += (v >> i) & 1;
            }
            ans = std::min(ans, now);
        }

        return ans;
    }
};

int main()
{
    ORSolitaire run;
    printf("%d\n", run.getMinimum(
                {1, 2, 4},
                7
            )
          );
    return 0;
}
