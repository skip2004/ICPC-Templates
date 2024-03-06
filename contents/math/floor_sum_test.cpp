#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
u64 floor_sum(u64 n, u64 m, u64 a, u64 b) {
	u64 ans = 0;
	for(;;) {
		if(a >= m) {
			ans += n * (n - 1) / 2 * (a / m);
			a %= m;
		}
		if(b >= m) {
			ans += n * (b / m);
			b %= m;
		}
		u64 ymax = a * n + b;
		if(ymax < m) break;
		n = ymax / m;
		b = ymax % m;
		std::swap(m, a);
	}
	return ans;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	u64 sum = 0;
	for(int i = 0;i < 10;++i) {
		sum += (2 * i + 5) / 3;
	}
	cout << sum << '\n';
	cout << floor_sum(10, 3, 2, 5) << '\n';
}
