struct oc {
	std::vector<int> f, g, res;
	std::vector<std::vector<int>> fa, fb;
	int n, p;
	oc(int n) : f(n), g(n), res(n), n(n), p(0) { }
	void push(int v0, int v1) {
		f[p] = v0;
		res[p] = (res[p] + (u64) f[0] * v1 + (u64) g[0] * v0) % mod;
		g[p++] = v1;
		static int A[N], B[N];
		int lb = p & -p;
		init(lb * 2);
		memset(A, 0, lim << 2);
		memset(B, 0, lim << 2);
		for(int i = 0;i < lb;++i) A[i] = g[p - lb + i], B[i] = f[p - lb + i];
		DFT(A), DFT(B);
		if(lb == p) {
			fa.emplace_back(A, A + lim);
			fb.emplace_back(B, B + lim);
			for(int i = 0;i < lim;++i) A[i] = (u64) A[i] * B[i] % mod;
		} else {
			auto & C = fb[std::__lg(lim)], & D = fa[std::__lg(lim)];
			for(int i = 0;i < lim;++i) A[i] = ((u64) A[i] * C[i * 2] + (u64) B[i] * D[i * 2]) % mod;
		}
		IDFT(A);
		for(int j = p;j < p + lb && j < n;++j) res[j] = (res[j] + A[j - p + lb]) % mod;
	}
};
struct Exp : oc {
	std::vector<int> ans;
	Exp(int n) : oc(n), ans(n) { }
	void push(int v) {
		if(!ans[0]) return void(ans[0] = 1);
		oc::push(ans[p], v * u64(p + 1) % mod);
		ans[p] = (u64) res[p - 1] * inv[p] % mod;
	}
};
struct Ln : oc {
	std::vector<int> ans; int fi;
	Ln(int n) : oc(n), ans(n), fi(0) {}
	void push(int v) {
		if(!fi) return void(fi = 1);
		oc::push(ans[p] * (u64) p % mod, v);
		ans[p] = ((u64) v * p + mod - res[p - 1]) % mod * inv[p] % mod;
	}
};
