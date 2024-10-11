#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;
const int N = 505;
using set = std::bitset<N>;
set edge[N];
std::vector<int> match(int nl, int nr) {
	set unvis; unvis.set();
	std::vector<int> match(nr + 1), ret(nl + 1);
	auto dfs = [&](auto dfs, int x) {
		for(set z = edge[x];;) {
			z &= unvis;
			int y = z._Find_first();
			if(y == N) return 0;
			if(unvis.reset(y), !match[y] || dfs(dfs, match[y])) {
				return match[y] = x, 1;
			}
		}
	};
	for(int i = 1;i <= nl;++i) 
		if(dfs(dfs, i)) unvis.set();
	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
	return ret[0] = 0, ret;
}

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int nl, nr, m;
	cin >> nl >> nr >> m;
	for(int i = 1, x, y;i <= m;++i) {
		cin >> x >> y;
		edge[x].set(y);
	}
	auto res = match(nl, nr);
	int ans = 0;
	for(int x : res) ans += x > 0;
	cout << ans << '\n';
	for(int i = 1;i <= nl;++i) {
		cout << res[i] << " \n"[i == nl];
	}
}
