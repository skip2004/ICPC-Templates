//https://judge.yosupo.jp/submission/201007
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
u64 floor_sum(u64 n, u64 m, u64 a, u64 b) {
	u64 ans = 0;
	for(;;) {
		if(a >= m) ans += n * (n - 1) / 2 * (a / m), a %= m;
		if(b >= m) ans += n * (b / m), b %= m;
		u64 ymax = a * n + b; // use u128 if it's big
		if(ymax < m) break;
		n = ymax / m;
		b = ymax % m;
		std::swap(m, a);
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int T; cin >> T;
	for(int i = 0;i < T;++i) {
		int n, m, a, b;
		cin >> n >> m >> a >> b;
		cout << floor_sum(n, m, a, b) << '\n';
	}
}
