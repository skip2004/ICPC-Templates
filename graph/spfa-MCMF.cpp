using ll = long long;
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
	ll d[N];
	int vis[N], fr[N];
	bool spfa(int s, int t) {
		std::queue<int> Q;
		std::fill(d + s, d + t + 1, 1e18);
		for(d[s] = 0, Q.push(s);!Q.empty();) {
			int x = Q.front(); Q.pop(); vis[x] = 0;
			for(int i = h[x];i;i = e[i].nxt)
				if(e[i].v && d[e[i].to] > d[x] + e[i].f) {
					d[e[i].to] = d[x] + e[i].f, fr[e[i].to] = i;
					if(!vis[e[i].to]) vis[e[i].to] = 1, Q.push(e[i].to);
				}
		}
		return d[t] < 1e17;
	}
	std::pair<ll, ll> EK(int s, int t) {
		ll f = 0, c = 0;
		for(;spfa(s, t);) {
			ll fl = 1e18;
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) fl = std::min<ll>(e[i].v, fl);
			f += fl, c += fl * d[t];
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) 
				e[i].v -= fl, e[i ^ 1].v += fl;
		}
		return std::make_pair(f, c);
	}
}
