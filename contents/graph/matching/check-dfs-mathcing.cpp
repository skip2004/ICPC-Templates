#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;
const int N = 505;

std::vector<int> edge[N];
std::vector<int> match(int nl, int nr) {
	std::vector<int> vis(nr + 1), match(nr + 1), ret(nl + 1);
	auto dfs = [&](auto dfs, int x) -> int {
		for(int y : edge[x]) if(!vis[y]) 
			if(vis[y] = 1, !match[y] || dfs(dfs, match[y]))
				return match[y] = x, 1;
		return 0;
	};
	for(int i = 1;i <= nl;++i) if(dfs(dfs, i))
		memset(vis.data(), 0, vis.size() << 2);
	for(int i = 1;i <= nr;++i) if(int t = match[i]) ret[t] = i;
	return ret;
}
std::array<std::vector<int>, 3> minedgeconver(int nl, int nr) {
	std::vector<int> vis(nr + 1), match(nr + 1), ret(nl + 1);
	auto dfs = [&](auto dfs, int x) -> int {
		for(int y : edge[x]) if(!vis[y]) 
			if(vis[y] = 1, !match[y] || dfs(dfs, match[y]))
				return match[y] = x, 1;
		return 0;
	};
	for(int i = 1;i <= nl;++i) if(dfs(dfs, i))
		memset(vis.data(), 0, vis.size() << 2);
	for(int i = 1;i <= nr;++i) if(int t = match[i]) ret[t] = i;
	for(int i = 1;i <= nl;++i) if(!ret[i]) dfs(dfs, i);
	std::vector<int> le, ri;
	for(int i = 1;i <= nl;++i) if(ret[i] && !vis[ret[i]]) le.push_back(i);
	for(int i = 1;i <= nr;++i) if(vis[i]) ri.push_back(i);
	return {le, ri, ret};
}

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int nl, nr, m;
	cin >> nl >> nr >> m;
	for(int i = 1, x, y;i <= m;++i) {
		cin >> x >> y;
		edge[x].push_back(y);
	}
	auto [l, r, res] = minedgeconver(nl, nr);
	std::vector<int> okl(nl + 1), okr(nr + 1);
	for(int x : l) okl[x] = 1;
	for(int x : r) okr[x] = 1;
	for(int i = 1;i <= nl;++i) {
		if(okl[i]) continue;
		for(int x : edge[i]) {
			assert(okr[x]);
		}
	}
	int ans = 0;
	for(int x : res) ans += x > 0;
	cout << ans << '\n';
	for(int i = 1;i <= nl;++i) {
		cout << res[i] << " \n"[i == nl];
	}
}
