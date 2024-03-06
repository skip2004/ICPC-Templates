// S 编号最小，T 最大，或者改一下清空
struct Dinic {
	struct T {
		int to, nxt, v;
	} e[N << 3];
	int h[N], head[N], num = 1;
	void link(int x, int y, int v) {
		e[++num] = {y, h[x], v}, h[x] = num;
		e[++num] = {x, h[y], 0}, h[y] = num; // !!!
	}
	int dis[N];
	bool bfs(int s, int t) {
		std::queue<int> Q;
		for(int i = s;i <= t;++i) dis[i] = -1, head[i] = h[i]; //如果编号不是[S,T]，只要改这里
		for(Q.push(t), dis[t] = 0;!Q.empty();) {
			int x = Q.front(); Q.pop();
			for(int i = h[x];i;i = e[i].nxt) if(e[i ^ 1].v && dis[e[i].to] < 0) {
				dis[e[i].to] = dis[x] + 1, Q.push(e[i].to);
			}
		}
		return dis[s] >= 0;
	}
	int dfs(int s, int t, int lim) {
		if(s == t || !lim) return lim;
		int ans = 0, mn;
		for(int & i = head[s];i;i = e[i].nxt) {
			if(dis[e[i].to] + 1 == dis[s] && (mn = dfs(e[i].to, t, std::min(lim, e[i].v)))) {
				e[i].v -= mn, e[i ^ 1].v += mn;
				ans += mn, lim -= mn;
				if(!lim) break;
			}
		}
		return ans;
	}
	int flow(int s, int t) {
		int ans = 0;
		for(;bfs(s, t);) ans += dfs(s, t, 1e9);
		return ans;
	}
} G;
