#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
std::vector<int> manacher(const std::string & s, bool is_even) {
	const int N = s.size() - is_even;
	std::vector<int> o(N); // 半径
	for(int i = 0, mid = 0, r = 0;i < N;++i) {
		int & x = o[i] = 0;
		if(i < r) x = std::min(r - i, o[mid - i]);
		for(;i - x >= 0 && i + x < N && s[i - x] == s[i + x + is_even];)
			++ x;
		if(i + x > r) {
			mid = i * 2;
			r = i + x;
		}
	}
	return o;
}
std::vector<int> naive(const std::string & s, bool is_even) {
	const int N = s.size() - is_even;
	std::vector<int> o(N);
	for(int i = 0;i < N;++i) {
		int & x = o[i] = 0;
		for(;i - x >= 0 && i + x < N && s[i - x] == s[i + x + is_even];) {
			++ x;
		}
	}
	return o;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::mt19937 gen;
	for(int i = 0;i < 1e5;++i) {
		int n = gen() % 30 + 1, is_even = gen() % 2;
		std::string s;
		for(int i = 0;i < n;++i) {
			s += char('a' + std::min(gen() % 3, gen() % 3));
		}
		auto A = manacher(s, is_even), B = naive(s, is_even);
		if(A != B) {
			std::cerr << s << ' ' << is_even << '\n';
			return 0;
		}
	}
}
