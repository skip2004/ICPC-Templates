// 匈牙利，左到右单向边，O(M|match|)
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
/* 最小边覆盖，很可能没用，真别抄，抄这个不用抄 match */
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
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// 匈牙利，左到右单向边，bitset，O(n^2/w |match|)
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
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
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// HK, 左到右单向边，O(M sqrt(|match|))
// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
std::vector<int> edge[N];
std::vector<int> L, R, vis, matchl, matchr;
bool bfs(int nl, int nr) {
	L.assign(nl + 1, 0), R.assign(nr + 1, 0);
	static std::queue<int> Q;
	for(int i = 1;i <= nl;++i) 
		if(!matchl[i]) L[i] = 1, Q.push(i);
	int succ = 0;
	for(;Q.size();) {
		int x = Q.front(); Q.pop();
		for(int i : edge[x]) if(!R[i]) {
			R[i] = L[x] + 1;
			if(int p = matchr[i]) L[p] = R[i] + 1, Q.push(p);
			else succ = 1;
		}
	}
	return succ;
}
bool dfs(int x) {
	for(int i : edge[x]) if(R[i] == L[x] + 1 && !vis[i]) {
		vis[i] = 1;
		if(!matchr[i] || dfs(matchr[i])) 
			return matchl[x] = i, matchr[i] = x, 1;
	}
	return 0;
}
std::vector<int> match(int nl, int nr) {
	matchl.assign(nl + 1, 0);
	matchr.assign(nr + 1, 0);
	vis.resize(nr + 1);
	for(;bfs(nl, nr);) {
		memset(vis.data(), 0, vis.size() << 2);
		for(int i = 1;i <= nl;++i) if(!matchl[i]) dfs(i);
	}
	return matchl;
}
/* 最小边覆盖，很可能没用，真别抄 */
std::pair<std::vector<int>, std::vector<int>> minedgecover(int nl, int nr) {
	auto res = match(nl, nr);
	std::vector<int> ls, rs;
	for(int i = 1;i <= nl;++i) if(!L[i]) ls.push_back(i);
	for(int i = 1;i <= nr;++i) if(R[i]) rs.push_back(i);
	return std::make_pair(ls, rs);
}
