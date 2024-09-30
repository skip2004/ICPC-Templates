int bostan_mori(fps p, fps q, ll k) {
	int n = q.size();
	for(;k;k >>= 1) {
		auto nq = q;
		for(int i = 1;i < n;i += 2) nq[i] = mod - nq[i];
		auto u = conv(p, nq), v = conv(q, nq);
		int t = k & 1, m = (size(u) + 1 - t) / 2;
		p.resize(m);
		for(int i = 0;i < m;++i) p[i] = u[i * 2 + t];
		for(int i = 0;i < n;++i) q[i] = v[i * 2];
	}
	return pow(q[0], mod - 2, p[0]);
}
