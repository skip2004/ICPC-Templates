ll e[N][N];
std::vector<int> KM(int n, int m) {
	std::vector<ll> l(n + 1), r(m + 1);
	std::vector<int> p(m + 1), ans(n + 1);
	for(int i = 1;i <= n;++i) {
		std::vector<ll> d(m + 1, 1e18);
		std::vector<int> pre(m + 1), done(m + 1);
		int x, v, u = 0;
		for(p[0] = i;x = p[u];u = v) {
			done[u] = 1;
			ll min = 1e18;
			for(int j = 1;j <= m;++j) if(!done[j]) {
				auto w = e[x][j] - l[x] - r[j];
				if(w < d[j]) d[j] = w, pre[j] = u;
				if(d[j] < min) min = d[j], v = j;
			}
			for(int j = 0;j <= m;++j) {
				if(done[j]) l[p[j]] += min, r[j] -= min;
				else d[j] -= min;
			}
		}
		for(int v;u;u = v) {
			v = pre[u], p[u] = p[v];
		}
	}
	for(int j = 1;j <= m;++j) ans[p[j]] = j;
	return ans; // 权值和 : -r[0]
}
