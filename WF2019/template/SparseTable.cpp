template<size_t size, size_t log_size>
struct SparseTable {
    int max[size][log_size], bit[size];
    void init(int *a, int n) {
        for (int i = 2; i <= n; ++i)bit[i] = bit[i >> 1] + 1;
        for (int i = 1; i <= n; ++i)max[i][0] = a[i];
        for (int j = 1; j <= bit[n]; ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                max[i][j] = std::max(max[i][j - 1], max[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
   int rmq(int l, int r) {
        int i = bit[r - l + 1];
        return std::max(max[l][i], max[r - (1 << i) + 1][i]);
    }
};
