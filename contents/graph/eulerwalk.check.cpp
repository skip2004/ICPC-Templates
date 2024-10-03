// https://uoj.ac/problem/117
#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;
using pr = std::pair<int, int>;
const int N = 500005;
std::vector<pr> e[N]; // (dest, id)
std::vector<pr> eulerwalk(int n, int m, int src) {
	std::vector<int> d(n + 1), it(n + 1), vis(m + 1);
	std::vector<pr>	ret, s = {pr(src, -1)};
//	++ d[src]; // 如果需要欧拉路径，加上这行
	for(;s.size();) {
		auto [x, id] = s.back();
		int & i = it[x];
		if(i == (int) e[x].size()) {
			ret.push_back(s.back()), s.pop_back();
			continue;
		}
		auto [y, o] = e[x][i++];
		if (!vis[o]) {
			-- d[x], ++ d[y];
			vis[o] = 1, s.emplace_back(y, o);
		}
	}
	for(int x : d) if(x < 0 || size(ret) != m + 1) return {};
	return std::vector(ret.rbegin(), ret.rend());
}
int t;
int n, m;
int u[N], v[N];
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> t >> n >> m;
	for(int i = 1;i <= m;++i) {
		cin >> u[i] >> v[i];
		e[u[i]].emplace_back(v[i], i);
		if(t == 1) e[v[i]].emplace_back(u[i], i);
	}
	auto res = eulerwalk(n, m, u[1]);
	if(res.size()) {
		cout << "YES" << '\n';
		for(int i = 1;i <= m;++i) {
			auto [x, id] = res[i];
			cout << (v[id] == x ? id : -id) << ' ';
		}
	} else {
		cout << "NO" << '\n';
	}
}
