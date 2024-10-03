// https://www.luogu.com.cn/problem/P1368
#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;

int minrep(const std::vector<int> & s) {
	int k = 0, i = 0, j = 1, n = size(s);
	for(;k < n && i < n && j < n;) {
		if(int d = s[(i + k) % n] - s[(j + k) % n]) {
			(d > 0 ? i : j) += k + 1;
			i += i == j, k = 0;
		} else {
			++ k;
		}
	}
	return std::min(i, j);
} // rotate(s.begin(), s.begin() + minrep(s), s.end());
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	std::vector<int> a(n);
	for(int i = 0;i < n;++i) {
		cin >> a[i];
	}
	rotate(a.begin(), a.begin() + minrep(a), a.end());
	for(int i = 0;i < n;++i) {
		cout << a[i] << ' ';
	}
}
