using fps = std::vector<int>;
fps comp(fps f, fps g, int n) {
	int S = 4 << std::__lg((n - 1) | 1);
	f.resize(S), g.resize(S * 2);
	for(int i = S / 2 - 1;i >= 0;--i) {
		f[i * 2] = f[i], f[i * 2 + 1] = 0;
		g[i] = g[i] ? mod - g[i] : 0;
	}
	auto dc = [&](auto dc, fps & P, fps & Q, int d, int n) {
		if(n == 1) return ;
		fps V(S * 2);
		for(int i = 0;i < S;++i) if(i & n) Q[i] = 0;
		Q[S] = 1, init(S * 2), DFT(data(Q));
		for(int i = 0;i < S;++i) V[i] = (u64) Q[i] * Q[i + S] % mod;
		init(S), IDFT(data(V)), V[0] = 0;
		dc(dc, P, V, d * 2, n / 2);
		init(S), DFT(data(P));
		for(int k = 0;k < S;++k) {
			int u = Q[k], v = Q[k + S], w = P[k];
			Q[k] = (u64) v * w % mod;
			Q[k + S] = (u64) u * w % mod;
		}
		init(S * 2), IDFT(data(Q));
		for(int i = 0;i < S;++i) P[i] = (i & n) ? 0 : Q[i + S];
	};
	dc(dc, f, g, 1, S / 2);
	f.resize(n);
	return f;
}
