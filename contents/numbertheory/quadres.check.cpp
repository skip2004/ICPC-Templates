#include<bits/stdc++.h>

using std::cin, std::cout;
using u64 = unsigned long long;

bool quadresnaive(u64 a, u64 b) {
	for(int i = 0;i < b;++i) if(i * i % b == a) return 1;
	return 0;
}
bool quadres(u64 a, u64 b) {
	if(a <= 1) return 1;
	for(;a % 4 == 0;) a /= 4;
	if(a % 2) return (a % 4 == 1 || b % 4 == 1) == quadres(b % a, a);
	return (b % 8 == 1 || b % 8 == 7) == quadres(a / 2, b);
}
int sqrtp(int x, int p) {
	if(x <= 1) return x;
	static std::mt19937_64 gen;
	int w, v, k = (p + 1) / 2;
	do w = gen() % p; while(quadres(v = ((u64) w * w + p - x) % p, p));
	using ai = std::array<int, 2>;
	auto prod = [&](ai x, ai y) {
		return ai{
			((u64) x[0] * y[0] + (u64) x[1] * y[1] % p * v) % p,
			((u64) x[0] * y[1] + (u64) x[1] * y[0]) % p
		};
	};
	ai ans{1, 0}, a{w, 1};
	for(;k;k >>= 1, a = prod(a, a))
		if(k & 1) ans = prod(ans, a);
	return ans[0];
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	for(int b = 1;b <= 3000;++b) {
		int np = 0;
		for(int x = 2;x < b;++x) if(b % x == 0) np = 1;
		if(np) continue;
		for(int i = 0;i < b;++i) {
			if(quadres(i, b) != quadresnaive(i, b)) {
				std::cerr << " wa " << i << ' ' << b << '\n';
				return 0;
			}
			if(1 || quadres(i, b)) {
				int v = sqrtp(i, b);
				assert(v != -1);
				assert(!quadres(i, b) || (u64) v * v % b == i);
			}
		}
	}
}
