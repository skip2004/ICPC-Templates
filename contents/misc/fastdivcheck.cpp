struct Divcheck {
	u64 inv, l;
	Divcheck(u64 p) {
		inv = p, l = -1ull / p;
		for(int j = 0;j < 5;++j) inv *= 2 - inv * p;
	}
	bool check(u64 x) const {
		return x * inv <= l;
	}
};
struct Divcheckll {
	u64 inv; ll l, r;
	Divcheckll(ll p) {
		inv = p, l = LLONG_MIN / p, r = LLONG_MAX / p;
		for(int j = 0;j < 5;++j) inv *= 2 - inv * p;
	}
	bool check(ll x) const {
		return x *= inv, l <= x && x <= r;
	}
};
