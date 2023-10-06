ll rho(ll n) {
	if(!(n & 1)) return 2;
	static std::mt19937_64 gen((size_t)"hehezhou");
	ll c = gen() % (n - 1) + 1, y = gen() % (n - 1) + 1;
	auto f = [&](ll o) {
		o = mul(o, o) + c;
		return o >= n ? o - n : o;
	};
	setmod(p);
	for(int l = 1;;l <<= 1) {
		ll x = y, g = 1;
		for(int i = 0;i < l;++i) y = f(y);
		const int d = 512;
		for(int i = 0;i < l;i += d) {
			ll sy = y;
			for(int j = 0;j < std::min(d, l - i);++j) {
				y = f(y), g = mul(g, (y - x + n));
			}
			g = std::__gcd(n, g);
			if(g == 1)
				continue;
			if(g == n)
				for(g = 1, y = sy;g == 1;)
					y = f(y), g = std::__gcd(n, y - x + n);
			return g;
		}
	}
}
std::vector<ll> factor(ll x) {
	std::queue<ll> q; q.push(x);
	std::vector<ll> res;
	for(;q.size();) {
		ll x = q.front(); q.pop();
		if(x == 1) continue;
		if(checkprime(x)) {
			res.push_back(x);
			continue;
		}
		ll y = rho(x);
		q.push(y), q.push(x / y);
	}
	sort(res.begin(), res.end());
	return res;
}
