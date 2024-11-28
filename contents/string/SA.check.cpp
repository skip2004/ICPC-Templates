//https://uoj.ac/submission/725738

#include<bits/stdc++.h>
using std::cin, std::cout;

auto SA(const std::vector<int> & s) {
	int n = s.size();
	std::vector<int> sa(n), gap(n), rk(n), h(n - 1);
	std::vector<std::array<int, 2>> o(n);
	gap[0] = 1;
	for(int i = 0;i < n;++i) o[i] = {s[i], i};
	for(int L = 1;;L *= 2) {
		for(int p = n, i = n - 1;i >= 0;--i) if(gap[i]) {
			sort(o.begin() + i, o.begin() + p, [](auto u, auto v) { return u[0] < v[0]; });
			for(;--p > i;) gap[p] = o[p][0] != o[p - 1][0];
		}
		int s = 0;
		for(int i = 0;i < n;++i) rk[o[i][1]] = s += gap[i];
		if(s == n) break;
		for(auto & [v, p] : o) v = p + L < n ? rk[p + L] : 0;
	}
	for(int i = 0;i < n;++i) sa[i] = o[i][1];
	for(int i = 0, k = 0;i < n;++i) if(rk[i] != n) {
		int j = sa[rk[i]];
		for(k -= !!k;i + k < n && j + k < n && s[i + k] == s[j + k];++k);
		h[rk[i] - 1] = k;
	}
	return std::pair(sa, h);
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::string s;
	cin >> s;
	std::vector<int> v(s.begin(), s.end());
	auto [sa, h] = SA(v);
	for(int x : sa) cout << x + 1 << ' ';
	cout << '\n';
	for(int x : h) cout << x << ' ';
	cout << '\n';
}
