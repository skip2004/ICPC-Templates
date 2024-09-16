#include<bits/stdc++.h>
#define rep(i, l, r) for(int i = (l), i##end = (r);i <= i##end;++i)
using std::cin;
using std::cout;

typedef unsigned long long u64;
typedef double db;
typedef long long ll;
typedef unsigned u32;
int n, m;
std::vector<int> Zalgo(const std::string & s) {
	std::vector<int> lcp(s.size());
	lcp[0] = s.size();
	for(int i = 1, l = 0, r = 0;i < (int) s.size();++i) {
		int & x = lcp[i];
		if(i < r) x = std::min(lcp[i - l], r - i);
		for(;i + x < (int) s.size() && s[x] == s[i + x];)
			++ x;
		if(i + x > r) l = i, r = i + x;
	}
	return lcp;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::string a, b;
	cin >> a >> b;
	auto lcp = Zalgo(b + a);
	u64 ans[2] = {};
	for(int i = 0;i < (int) b.size();++i) {
		ans[0] ^= (u64) (i + 1) * (std::min<int>(lcp[i], b.size() - i) + 1);
	}
	for(int i = 0;i < (int) a.size();++i) {
		ans[1] ^= (u64) (i + 1) * (std::min<int>(lcp[i + b.size()], b.size()) + 1);
	}
	for(auto x : ans)
		cout << x << '\n';
}

