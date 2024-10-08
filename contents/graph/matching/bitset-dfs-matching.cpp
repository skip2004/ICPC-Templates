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
