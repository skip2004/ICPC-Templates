using u64 = unsigned long long;
using u128 = __uint128_t;
struct mont {
	u64 p, pr, r;
	mont(u64 p) : p(p) { 
		pr = p, r = (-u128(p)) % p;
		for(int i = 0;i < 6;++i) pr *= 2 - p * pr;
	}
	u64 reduce(u128 x) const {
		u64 c = x, d = x >> 64;
		return d + p - u64(u128(c * pr) * p >> 64);
	}
	u64 raw(u64 x) const { return reduce(x * u128(r)); }
	u64 val(u64 x) const { return x = reduce(x), x >= p ? x - p : x; }
};
