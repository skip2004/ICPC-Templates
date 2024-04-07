#include<bits/stdc++.h>
using std::cin, std::cout;
using ll = long long;
using cp = std::complex<ll>;
std::pair<cp, cp> fracBS(ll n, ll m, auto f) {
	bool dir = 1, A = 1, B = 1;
	cp lo(0, 1), hi(1, 0); // hi can be (1, 0), f(hi) must be true
	if (f(lo)) return {lo, {}};
	while(A || B) {
		ll adv = 0, s = 1;
		for (int x = 0;s;(s *= 2) >>= x) {
			adv += s;
			cp mid = lo * adv + hi;
			if (mid.real() > n || mid.imag() > m || dir == !f(mid)) {
				adv -= s, x = 2;
			}
		}
		hi += lo * adv, dir = !dir;
		swap(lo, hi);
		A = B, B = adv;
	}
	return {dir ? hi : lo, dir ? lo : hi};
} // 返回值是最小的使得 f 为真的
  // 另外一个是最大的使得 f 为假的
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::mt19937 gen;
	for(;;) {
		int n = gen() % 1000 + 1;
		int m = gen() % 1000 + 1;
		std::vector<cp> v;
		for(int i = 1;i <= n;++i) {
			for(int j = 1;j <= m;++j) {
				if(std::gcd(i, j) == 1) {
					v.emplace_back(i, j);
				}
			}
		}
		auto less = [](cp x, cp y) {
			return x.real() * y.imag() < y.real() * x.imag();
		};
		sort(v.begin(), v.end(), less);
		for(int i = 0;i < 50000;++i) {
			int pos = gen() % (v.size() - 1);
			cp t = v[pos];
			auto cmp = [&](cp x) { return less(t, x); };
			auto [A, B] = fracBS(n, m, cmp);
			assert(A == v[pos + 1]);
			assert(B == v[pos]);
		}
		static int cnt = 0;
		std::cerr << "check " << ++ cnt << '\n';
	}
}
