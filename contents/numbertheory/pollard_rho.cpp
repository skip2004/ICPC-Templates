ll rho(ll n) {
	if(!(n & 1)) return 2;
	static std::mt19937_64 gen(42);
	ll x = 0, y = 0, prod = 1, g = gen() % n;
	auto f = [&](ll o) { return mul(o, o) + g; };
	for(int t = 28, z = 0;t % 32 || std::gcd(prod, n) == 1;++t) {
		if(ll q = mul(prod, x - y)) prod = q;
		else y = x = ++z, g = gen() % n;
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
