using set = std::bitset<N>;
// re 是反向边，需要连好
set e[N], re[N], vis;
std::vector<int> sta;
void dfs0(int x, set * e) {
	vis.reset(x);
	for(;;) {
		int go = (e[x] & vis)._Find_first();
		if(go == N) break;
		dfs0(go, e);
	}
	sta.push_back(x);
}
std::vector<std::vector<int>> solve() {
	vis.set();
	for(int i = 1;i <= n;++i) if(vis.test(i)) dfs0(i, e);
	vis.set();
	auto s = sta;
	std::vector<std::vector<int>> ret;
	for(int i = n - 1;i >= 0;--i) if(vis.test(s[i])) {
		sta.clear(), dfs0(s[i], re), ret.push_back(sta);
	}
	return ret;
}
