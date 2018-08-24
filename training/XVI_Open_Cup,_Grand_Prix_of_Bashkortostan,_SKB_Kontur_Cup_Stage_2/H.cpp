#include <bits/stdc++.h>

const int max_N = (int) 1e5 + 21;

struct node {
    char name[13];
    int D, birth, id;
} p[max_N];

int n, tot, department_tot, department_cnt[max_N];

struct department_cmp {
    bool operator() (int x, int y) const {
        if (p[x].birth != p[y].birth) return p[x].birth < p[y].birth;
        return p[x].id < p[y].id;
    }
};

std::unordered_map<int, int> department_id;
std::set<int, department_cmp> department[max_N];
std::unordered_map<int, int> empolyee[max_N];

struct office_cmp {
    bool operator() (int x, int y) const {
        if (p[x].birth != p[y].birth) return p[x].birth < p[y].birth;
        if (p[x].D != p[y].D) return p[x].D < p[y].D;
        return p[x].id < p[y].id;
    }
};

std::set<int, office_cmp> office;

char s[233];

int calc(int l, int r) {
    int x = 0;
    for (int i = l; i < r; ++i) {
        (x *= 10) += (s[i] - '0');
    }
    return x;
}

int getDepartID(int D) {
    if (!department_id.count(D)) department_id[D] = ++department_tot;
    return department_id[D];
}

std::string ans1, ans2;

void add() {
    ++tot;
    scanf("%d", &p[tot].D);
    scanf("%s", p[tot].name);
    scanf("%s", s);
    p[tot].birth = calc(6, 10) * 10000 + calc(3, 5) * 100 + calc(0, 2);
    // printf("p[%d].birth = %d\n", tot, p[tot].birth);
    int depart_id = getDepartID(p[tot].D);
    p[tot].id = ++department_cnt[depart_id];
    empolyee[depart_id][p[tot].id] = tot;
    office.insert(tot), ans1 = p[*office.begin()].name;
    department[depart_id].insert(tot), ans2 = p[*department[depart_id].begin()].name;
    printf("%s %s\n", ans1.c_str(), ans2.c_str());
}

void del() {
    int D, id;
    scanf("%d%d", &D, &id);
    int depart_id = getDepartID(D);
    int x = empolyee[depart_id][id];
    office.erase(x), ans1 = office.empty() ? "Vacant" : p[*office.begin()].name;
    department[depart_id].erase(x), ans2 = department[depart_id].empty() ? "Vacant" : p[*department[depart_id].begin()].name;
    printf("%s %s\n", ans1.c_str(), ans2.c_str());
}

int main() {
    scanf("%d", &n);
    for (int i = 1, t; i <= n; ++i) {
        scanf("%d", &t);
        if (t == 1) add();
        else del();
    }
    return 0;
}
