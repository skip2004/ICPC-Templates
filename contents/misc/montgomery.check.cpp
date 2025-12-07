#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
using db = double;
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
const u64 mod = -1ull >> 2;
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::mt19937_64 gen(42);
	int n = 3000;
	mont P(mod);
	std::vector<u64> a(n), b(n), A(n), B(n);
	for(int i = 0;i < n;++i) {
		a[i] = gen() % mod;
		b[i] = gen() % mod;
		A[i] = P.raw(a[i]);
		B[i] = P.raw(b[i]);
	}
	for(int i = 0;i < n;++i) {
		u64 s0 = 0, s1 = 0;
		for(int j = 0;j <= i;++j) {
			s0 = (s0 + u128(a[j]) * b[i - j]) % mod;
			s1 += P.reduce(u128(A[j]) * B[i - j]);
			if(s1 >= mod * 1) s1 -= mod * 1;
			assert(s1 < mod * 2);
		}
		assert(s0 == P.val(s1));
	}
}
