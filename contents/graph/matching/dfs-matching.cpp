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
