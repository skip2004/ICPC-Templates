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
	std::vector<ll> res;
	auto f = [&](auto f, ll x) {
		if(x == 1) return ;
		if(checkprime(x)) return res.push_back(x);
		ll y = rho(x);
		f(f, y), f(f, x / y);
	};
	f(f, x), sort(res.begin(), res.end());
	return res;
}
