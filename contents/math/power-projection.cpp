fps PowerProjection(fps f, fps g, int n) {
	int m = 2 << std::__lg((n - 1) | 1), S = m * 2;
	reverse(f.begin(), f.end());
	f.insert(f.begin(), m + S, 0);
	f.resize(S * 2);
	g.resize(S * 2);
	for (int i = 0; i < m; ++i) g[i] = g[i] ? mod - g[i] : 0;
	for(;m > 1;m /= 2) {
		for(int i = 0;i < S * 2;++i) (i & m ? g[i] : f[i]) = 0;
		for(int i = 0;i < S;++i) g[i + S] = 0, f[i] = 0;
		g[S] = 1, init(S * 2), IDFT(f.data()), DFT(g.data());
		for (int i = 0; i < S; ++i) {
			u64 a = f[i], b = f[i + S];
			u64 c = g[i], d = g[i + S];
			f[i + S] = (a * d + b * c) % mod;
			g[i] = (u64)c * d % mod;
		}
		init(S), DFT(f.data() + S), IDFT(g.data()), g[0] = 0;
	};
	for(int i = 0;i < n;++i) f[i] = f[i * 2 + 1 + S];
	f.resize(n);
	return f;
}
