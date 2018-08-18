namespace circuits {
	//The number of connected blocks on the contour line will
	//not exceed half of the number of columns
	using LL = long long;

	const int max_N = 12;

	struct state {
		int a[max_N], n, m;

		state(int col, LL s) : n(col + 1) {
			m = 0;
			for (int i = n - 1; ~i; --i) {
				a[i] = (s & 7), s >>= 3, (a[i] > m) && (m = a[i]);
			}
			++m;
		}

		void minimal() {
			static int f[max_N];
			memset(f, -1, sizeof(f));
			f[0] = 0, m = 1;
			for (int i = 0; i < n; ++i) {
				if (f[a[i]] == -1) f[a[i]] = m++;
				a[i] = f[a[i]];
			}
		}

		void add(int u, int v) { a[u] = a[v] = m++; }

		void unite(int u, int v) {
			int b = a[u], c = a[v];
			for (int i = 0; i < n; ++i)
				if (a[i] == b) a[i] = c;
			a[u] = a[v] = 0;
		}

		void swap(int u, int v) { std::swap(a[u], a[v]); }

		LL hash() {
			minimal();
			LL s = 0;
			for (int i = 0; i < n; ++i) (s <<= 3) |= a[i];
			return s;
		}

		void move() {
			for (int i = n - 1; i; --i) a[i] = a[i - 1];
			a[0] = 0;
		}
	};

	std::unordered_map<LL, LL> pre, cur;
};