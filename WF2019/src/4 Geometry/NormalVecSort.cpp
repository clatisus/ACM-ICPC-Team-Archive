P p[max_N];
int n, Q[max_N], pos[max_N];
bool cmp(int a, int b) {
    if (p[a].x != p[b].x) return p[a].x < p[b].x;
    return std::make_pair(p[a].y, a) < std::make_pair(p[b].y, b);
}
struct vec {
    P v;
    int idl, idr;
    vec() = default;
    explicit vec(P v, int idl, int idr) : v(v), idl(idl), idr(idr) {}
    friend bool operator<(const vec &a, const vec&b) {
        LL t, t1, t2;
        if ((t1 = a.v.region()) != (t2 = b.v.region())) return t1 < t2;
        if ((t = a.v.det(b.v)) != 0) return t > 0;
        if ((t1 = a.v.dot(p[a.idr])) != (t2 = a.v.dot(p[b.idr]))) return t1 < t2;
        if (a.idr != b.idr) {
            if (p[a.idr] == p[b.idr]) return a.idr > b.idr;
            return a.v.det(p[a.idr]) < a.v.det(p[b.idr]);
        } else {
            if (p[a.idl] == p[b.idl]) return a.idl < b.idl;
            return a.v.det(p[a.idl]) < a.v.det(p[b.idl]);
        }
    }
};
std::vector<vec> vecs;
LL S;
inline LL area(int a, int b, int c) {
    return p[b].sub(p[a]).det(p[c].sub(p[a]));
}
void binaySearch(int a, int b, int l, int r) {
    while (l <= r) {
        int mid = (l + r) >> 1;
        LL ret = area(a, b, Q[mid]);
        if (ret <= 0) {
            r = mid - 1;
        } else {
            S = std::min(S, ret);
            l = mid + 1;
        }
    }
}
void solve(int a, int b) {
    int l = 0, r = pos[b] - 1;
    binaySearch(a, b, l, r);
    std::swap(a, b);
    l = pos[b] + 1, r = n - 1;
    binaySearch(a, b, l, r);
}
int main() {
    scanf("%d", &n);
    S = LLONG_MAX;
    for (int i = 0; i < n; ++i) {
        Q[i] = i;
        p[i].init();
    }
    std::sort(Q, Q + n, cmp);
    for (int i = 0; i < n; ++i) {
        pos[Q[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (p[i] == p[j]) continue;
            vecs.emplace_back(p[i].sub(p[j]), i, j);
        }
    }
    std::sort(vecs.begin(), vecs.end());
    for (auto &it : vecs) {
        if (pos[it.idl] < pos[it.idr]) {
            solve(it.idr, it.idl);
            continue;
        }
        solve(it.idl, it.idr);
        std::swap(Q[pos[it.idl]], Q[pos[it.idr]]);
        std::swap(pos[it.idl], pos[it.idr]);
    }
    printf("%.1f\n", S * 0.5);
}