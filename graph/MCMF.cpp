// S 编号最小，T 最大，或者改一下清空
namespace mcmf {
	using pr = std::pair<ll, int>;
	const int N = 10005, M = 1e6 + 10;
	struct edge {
		int to, nxt, v, f;
	} e[M << 1];
	int h[N], num = 1;
	void link(int x, int y, int v, int f) {
		e[++num] = {y, h[x], v, f}, h[x] = num;
		e[++num] = {x, h[y], 0, -f}, h[y] = num;
	}
	ll d[N], dis[N];
	int vis[N], fr[N];
	bool spfa(int s, int t) {
		std::queue<int> Q;
		std::fill(d + s, d + t + 1, 1e18);
		for(d[s] = 0, Q.push(s);!Q.empty();) {
			int x = Q.front(); Q.pop(); vis[x] = 0;
			for(int i = h[x];i;i = e[i].nxt)
				if(e[i].v && d[e[i].to] > d[x] + e[i].f) {
					d[e[i].to] = d[x] + e[i].f;
					fr[e[i].to] = i;
					if(!vis[e[i].to]) vis[e[i].to] = 1, Q.push(e[i].to);
				}
		}
		return d[t] < 1e17;
	}
	bool dijkstra(int s, int t) { // 正常题目不需要 dijk
		std::priority_queue<pr, std::vector<pr>, std::greater<pr>> Q;
		for(int i = s;i <= t;++i) dis[i] = d[i], d[i] = 1e18, vis[i] = 0;
		for(Q.emplace(d[s] = 0, s);!Q.empty();) {
			int x = Q.top().second; Q.pop();
			if(vis[x]) continue;
			vis[x] = 1;
			for(int i = h[x];i;i = e[i].nxt) {
				const ll v = e[i].f + dis[x] - dis[e[i].to];
				if(e[i].v && d[e[i].to] > d[x] + v) {
					fr[e[i].to] = i;
					Q.emplace(d[e[i].to] = d[x] + v, e[i].to);
				}
			}
		}
		for(int i = s;i <= t;++i) d[i] += dis[i];
		return d[t] < 1e17;
	}
	std::pair<ll, ll> EK(int s, int t) {
		spfa(s, t); // 如果初始有负权且要 dijk
		ll f = 0, c = 0;
		for(;dijkstra(s, t);) { // 正常可以用 spfa
			ll fl = 1e18;
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) fl = std::min<ll>(e[i].v, fl);
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) e[i].v -= fl, e[i ^ 1].v += fl;
			f += fl, c += fl * d[t];
		}
		return std::make_pair(f, c);
	}
}
