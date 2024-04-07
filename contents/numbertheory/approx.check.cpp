#include<bits/stdc++.h>
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;
const int mod = 1e6 + 3;
std::pair<int, int> approx(int p, int q, int A) {
	int x = q, y = p, a = 1, b = 0;
	for(;x > A;) {
		std::swap(x, y), std::swap(a, b);
		a -= x / y * b, x %= y;
	}
	return {x, a};
} // $q \equiv \frac{x}{a} \pmod{p}, x \leq A$, |a| 取到最小值
int pow(int a, int b, int ans = 1) {
	for(;b;b >>= 1, a = (u64) a * a % mod) if(b & 1)
		ans = (u64) ans * a % mod;
	return ans;
}

int main() {
	std::mt19937 gen(time(0) + (size_t) new char);
	for(int i = 0;i < 1e6;++i) {
		int x = gen() % (mod - 1) + 1;
		int A = gen() % (mod - 1) + 1;
		auto res = approx(mod, x, A);
		assert((1ll * res.second * x - res.first) % mod == 0);
		int inv = pow(x, mod - 2);
		for(int j = 1;j <= A;++j) {
			int z = (u64) inv * j % mod;
			assert(z >= std::abs(res.second));
			assert(mod - z >= std::abs(res.second));
		}
		if(i % 100 == 0)
		std::cerr << i << '\n';
	}
	return 0;
}

