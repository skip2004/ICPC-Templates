fps inv(fps a, int n) {
	static int res[N];
	if(a.size() < n) a.resize(n);
	inv(a.data(), res, n);
	return fps(res, res + n);
}
fps cut(const fps & f, int d) {
	return fps(f.begin(), f.begin() + std::min((int)f.size(), d));
}
fps revp(const fps & f) { return fps(f.rbegin(), f.rend()); }
std::pair<fps, fps> polydiv(fps f, fps g) {
	int n = size(f), gd = size(g) - 1, qd = n - gd;
	if (n <= gd) return {fps(), f};
	auto F = cut(revp(f), qd);
	auto G = inv(revp(g), qd);
	fps q = revp(cut(conv(F, G), qd));
	g = conv(g, q);
	for(int i = 0;i < gd;++i) f[i] = (f[i] + mod - g[i]) % mod;
	return {q, cut(f, gd)};
}
fps solve(fps p, fps q, u64 k, int m) { 
	const int d = size(q) - 1;
	auto rec = [&](auto rec, ll k) {
		if(k == 0) return d > 0 ? fps{1} : fps();
		if(k == 1) {
			int p = pow(q[0], mod - 2); fps res(d);
			for(int i = 0;i < d;++i) res[i] = u64(mod - p) * q[i + 1] % mod;
			return res;
		}
		fps f = rec(rec, (k + 1) / 2);
		f = conv(f, f);
		if(k & 1) f.insert(f.begin(), 0);
		return polydiv(f, q).second;
	};
	fps res = rec(rec, k);
	res = polydiv(conv(res, p), q).second;
	res = conv(res, inv(q, m));
	return fps(res.begin(), res.begin() + m);
} 
fps solve_x(fps p, fps q, u64 k, int m) { 
	auto [a, p0] = polydiv(p, q);
	auto ans = p0.size() ? solve(p0, q, k, m) : fps(m);
	for(int i = 0;i < m;++i) {
		if(k + i < (int) a.size()) ans[i] = (ans[i] + a[i + k]) % mod;
	}
	return ans;
}
