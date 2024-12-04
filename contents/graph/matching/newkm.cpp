std::vector<std::pair<int, ll>> e[N];
bool down(ll & x, ll y) { return x > y ? x = y, 1 : 0; }
auto KM(int n, int m) {
	std::vector<ll> h(n + 1), rv(m + 1);
	std::vector<int> R(m + 1);
	ll cost = 0;
	for(;;) {
		std::vector<ll> d(n + 1);
		std::vector<int> vis(n + 1), p0(n + 1), p1(m + 1);
		for(int i = 0;i <= m;++i) d[R[i]] = inf;
		for(int x = 0;vis[x] ^= 1;) {
			ll min = 1e18;
			for(auto [j, w] : e[x]) if(down(d[R[j]], d[x] + w - rv[j])) p0[R[j]] = j, p1[j] = x;
			for(int j = 1;j <= n;++j) if(!vis[j] && down(min, d[j] - h[j])) x = j;
		}
		if(d[0] >= inf / 2) break; // or inf/2=>0
		for(int r = p0[0];r;r = p0[R[r]]) {
			rv[r] += d[R[r]] - d[p1[r]];
			R[r] = p1[r];
		}
		cost += d[0], h = d;
	}
	return std::tuple(cost, R, rv);
}
