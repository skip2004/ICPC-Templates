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
