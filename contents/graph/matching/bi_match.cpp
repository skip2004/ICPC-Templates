// 匈牙利，左到右单向边，$O(M|match|)$
std::vector<int> edge[N];
bool dfs(int x, std::vector<int> & vis, std::vector<int> & match) {
	for(int y : edge[x]) if(!vis[y]) 
		if(vis[y] = 1, !match[y] || dfs(match[y], vis, match)) 
			return match[y] = x, 1;
	return 0;
}
std::vector<int> match(int nl, int nr) {
	std::vector<int> vis(nr + 1), match(nr + 1), ret(nl + 1);
	for(int i = 1;i <= nl;++i) if(dfs(i, vis, match)) 
		memset(vis.data(), 0, vis.size() << 2);
	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
	return ret[0] = 0, ret;
}
// 最小边覆盖
std::pair<std::vector<int>, std::vector<int>> minedgecover(int nl, int nr) {
	std::vector<int> vis(nr + 1), match(nr + 1), ret(nl + 1);
	for(int i = 1;i <= nl;++i) if(dfs(i, vis, match))
		memset(vis.data(), 0, vis.size() << 2);
	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
	ret[0] = 0;
	for(int i = 1;i <= nl;++i) if(!ret[i]) dfs(i, vis, match);
	std::vector<int> le, ri;
	for(int i = 1;i <= nl;++i) if(ret[i] && !vis[ret[i]]) le.push_back(i);
	for(int i = 1;i <= nr;++i) if(vis[i]) ri.push_back(i);
	return std::make_pair(le, ri);
}
// 匈牙利，左到右单向边，bitset，$O(n^2/w |match|)$
using set = std::bitset<N>;
set edge[N];
bool dfs(int x, set & unvis, std::vector<int> & match) {
	for(set z = edge[x];;) {
		z &= unvis;
		int y = z._Find_first();
		if(y == N) return 0;
		if(unvis.reset(y), !match[y] || dfs(match[y], unvis, match))
			return match[y] = x, 1;
	}
}
std::vector<int> match(int nl, int nr) {
	set unvis; unvis.set();
	std::vector<int> match(nr + 1), ret(nl + 1);
	for(int i = 1;i <= nl;++i) 
		if(dfs(i, unvis, match)) 
			unvis.set();
	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
	return ret[0] = 0, ret;
}
// HK, 左到右单向边，$O(M \sqrt{|match|})$
std::vector<int> e[N];
std::vector<int> matchl, matchr, a, p; 
std::vector<int> match(int nl, int nr) {
	matchl.assign(nl + 1, 0), matchr.assign(nr + 1, 0);
	for(;;) {
		a.assign(nl + 1, 0), p.assign(nl + 1, 0);
		static std::queue<int> Q;
		for(int i = 1;i <= nl;++i) 
			if(!matchl[i]) a[i] = p[i] = i, Q.push(i);
		int succ = 0;
		for(;Q.size();) {
			int x = Q.front(); Q.pop();
			if(matchl[a[x]]) continue;
			for(int y : e[x]) {
				if(!matchr[y]) {
					for(succ = 1;y;x = p[x])
						matchr[y] = x, std::swap(matchl[x], y);
					break;
				}
				if(!p[matchr[y]])
					Q.push(y = matchr[y]), p[y] = x, a[y] = a[x];
			}
		}
		if(!succ) break;
	}
	return matchl;
} // matchl 是左边每个点匹配的右边点编号
std::pair<std::vector<int>, std::vector<int>> minedgecover(int nl, int nr) {
	match(nl, nr);
	std::vector<int> l, r;
	for(int i = 1;i <= nl;++i) if(!a[i]) l.push_back(i);
	for(int i = 1;i <= nr;++i) if(a[matchr[i]]) r.push_back(i);
	return {l, r};
}
