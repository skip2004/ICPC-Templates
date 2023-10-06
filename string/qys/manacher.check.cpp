#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
std::vector<int> getrev(const std::string & s, bool is_even) {
	const int N = s.size() - is_even;
	std::vector<int> o(N); // 半径
	for(int i = 0, mid2 = 0, r = 0;i < N;++i) {
		int & x = o[i] = 0;
		if(i < r) x = std::min(r - i, o[mid2 - i]);
		for(;i - x >= 0 && i + x < N && s[i - x] == s[i + x + is_even];)
			++ x;
		if(i + x > r) {
			mid2 = i * 2 + is_even;
			r = i + x;
		}
	}
	return o;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::string s;
	cin >> s;
	auto a = getrev(s, 0);
	auto b = getrev(s, 1);
	cout << std::max(*max_element(a.begin(), a.end()) * 2 - 1, *max_element(b.begin(), b.end()) * 2) << '\n';
}
