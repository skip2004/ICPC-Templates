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
    std::vector<int> res;
    Exp(int n) : oc(n), res(n) { }
    void push(int v) {
        if(!res[0]) return void(res[0] = 1);
        oc::push(res[p], v * u64(p + 1) % mod);
        res[p] = (u64) oc::res[p - 1] * inv[p] % mod;
    }
};
struct Ln : oc {
    std::vector<int> res; int fi;
    Ln(int n) : oc(n), res(n), fi(0) {}
    void push(int v) {
        if(!fi) return void(fi = 1);
        oc::push(res[p] * (u64) p % mod, v);
        res[p] = ((u64) v * p + mod - oc::res[p - 1]) % mod * inv[p] % mod;
    }
};
struct Inv : oc {
    std::vector<int> res; int fi;
    Inv(int n) : oc(n), res(n), fi(0) {}
    void push(int v) {
		res[p] = fi ? (oc::res[p] + (u64) v * res[0]) % mod * (mod - res[0]) % mod : pow(fi = v, mod - 2);
        oc::push(res[p], v);
    }
};

