#include<bits/stdc++.h>
using std::cin, std::cout;
using u64 = unsigned long long;
using ll = long long;
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
std::mt19937_64 gen(time(0) + (size_t) new char);

void test1() {
	for(int i = 0;i < 1e7;++i) {
		ll mod = gen() >> (gen() % 64) >> 1;
		mod |= 1;
		Divcheckll P(mod);
		assert(P.inv * mod == 1);
		auto test = [&](ll x) {
			assert((x % mod == 0) == P.check(x));
		};
		for(int j = 0;j < 30;++j) {
			ll x = gen();
			test(x);
			test(x / mod * mod);
			test(x / mod * mod + 1);
			test(x / mod * mod - 1);
		}
	}
}
void test0() {
	for(int i = 0;i < 1e7;++i) {
		u64 mod = gen() >> (gen() % 64);
		mod |= 1;
		Divcheck P(mod);
		assert(P.inv * mod == 1);
		auto test = [&](u64 x) {
			assert((x % mod == 0) == P.check(x));
		};
		for(int j = 0;j < 30;++j) {
			u64 x = gen();
			test(x);
			test(x / mod * mod);
			test(x / mod * mod + 1);
			test(x / mod * mod - 1);
		}
	}
}

int main() {
	test1();
}
