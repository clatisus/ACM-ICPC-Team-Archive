#include <bits/stdc++.h>

class StoryFromTCO
{
public:
    int minimumChanges(std::vector<int> places, std::vector<int> cutoff) {
        std::vector<std::pair<int, int> > vec;
        std::multiset<int> select_p;
        std::multiset<int> select_c;
        std::multiset<int> set;

        int n = (int)(places.size());
        for (int i = 0; i < n; ++ i) {
            if (places[i] > cutoff[i]) {
                select_p.insert(places[i]);
                select_c.insert(cutoff[i]);
            } else {
                vec.push_back({places[i], cutoff[i]});
            }
        }

        std::sort(vec.begin(), vec.end());

        int ret = (int)(select_p).size();
        int m = ret;
        n = (int)(vec.size());
        for (int i = 0, j = 0; i < m; ++ i) {
            if (*select_p.begin() <= *select_c.begin()) {
                select_p.erase(select_p.begin());
                select_c.erase(select_c.begin());
            } else {
                while (j < n && vec[j].first <= *select_c.begin()) {
                    set.insert(vec[j ++].second);
                }
                if (!(int)(set.size())) {
                    return -1;
                }
                // the following two lines order does not matters
                select_c.insert(*(-- set.end()));
                select_c.erase(select_c.begin());

                set.erase(-- set.end());
                -- i;
                ++ ret;
            }
        }
        return ret;
    }
};

int main()
{
    StoryFromTCO run;
    printf("%d\n", run.minimumChanges(
                {20, 100, 500, 50}, 
                {7500, 2250, 150, 24}
                ));
    return 0;
}
