#include<bits/stdc++.h>
using std::cin, std::cout;
auto duval(const std::vector<int> & s) {
	int n = s.size();
	std::vector<std::vector<int>> res;
	for(int i = 0;i < n;) {
		int j = i + 1, k = i;
		for(;j < n && s[k] <= s[j];++j) {
			if(s[k] < s[j]) {
				k = i;
			} else {
				++ k;
			}
		}
		for(;i <= k;i += j - k) {
			res.emplace_back(s.begin() + i, s.begin() + i + (j - k));
		}
	}
	return res;
}
auto naive(std::vector<int> S) {
	using String = std::basic_string<int>;
    std::vector<String> s;
	int n = size(S);
	for (int i = 0; i < n; i++) {
		String c(1, S[i]);
		while (!s.empty() && s.back() + c < c) {
			c = s.back() + c;
			s.pop_back();
		}
		s.push_back(c);
	}
	std::vector<std::vector<int>> v;
	for(auto u : s) v.emplace_back(u.begin(), u.end());
	return v;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::mt19937 gen;
	for(int i = 0;i < 1e6;++i) {
		int len = gen() % 20 + 1;
		std::vector<int> v;
		for(int j = 0;j < len;++j) {
			v.push_back(std::min(gen() % 3, gen() % 3));
		}
		auto a = duval(v);
		auto b = naive(v);
		assert(a == b);
	}
	puts("OK!");
}
