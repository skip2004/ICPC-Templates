int minmod(int n, int m, int a, ll b) {
	int ans = m;
	for(;n;std::swap(a, m)) {
		a %= m, b %= m;
		if(b < 0) b += m;
		if(b < ans) ans = b;
		n = (ll(n - 1) * a + b) / m;
		b -= (ll) m * n;
	}
	return ans;
}
