ll rho(ll n) {
	if(!(n & 1)) return 2;
	static std::mt19937_64 gen((size_t)"hehezhou");
	ll x = 0, y = 0, prod = 1;
	auto f = [&](ll o) { return mul(o, o) + 1; };
	setmod(n);
	for(int t = 30, z = 0;t % 64 || std::gcd(prod, n) == 1;++t) {
		if (x == y) x = ++ z, y = f(x);
		if(ll q = mul(prod, x + n - y)) prod = q;
		x = f(x), y = f(f(y));
	}
	return std::gcd(prod, n);
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
