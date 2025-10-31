#include<bits/stdc++.h>
using std::cin, std::cout;
using ll = long long;
struct maxflow {
	int n;
	std::vector<std::vector<std::array<int, 2>>> e;
	std::vector<ll> f;
	maxflow(int s) : n(s + 1), e(n) { }
	void add(int x, int y, int v) {
		e[x].push_back({y, (int)f.size()}); 
		f.push_back(v);
		e[y].push_back({x, (int)f.size()}); 
		f.push_back(0);
	}
	ll flow(int s, int t, ll max = 1e18) {
		ll ans = 0;
		std::vector<int> dis(n), h(n);
		for(;ans < max;) {
			for(int i = 0;i < n;++i) dis[i] = -1, h[i] = e[i].size() - 1;
			std::queue<int> q;
			for(q.push(t), dis[t] = 0;q.size();) {
				int x = q.front(); q.pop();
				for(auto [y, id] : e[x]) if(dis[y] < 0 && f[id ^ 1]) {
					dis[y] = dis[x] + 1, q.push(y);
					if(y == s) break;
				}
			}
			if(dis[s] < 0) break;
			auto dfs = [&](auto dfs, int s, ll l) {
				if(s == t) return l;
				ll ans = 0;
				for(int & i = h[s];i >= 0;--i) {
					auto [y, id] = e[s][i];
					if(dis[y] + 1 != dis[s] || !f[id]) continue;
					ll w = dfs(dfs, y, std::min(l - ans, f[id]));
					f[id] -= w, f[id ^ 1] += w;
					ans += w;
					if(ans == l) return l;
				}
				dis[s] = -1;
				return ans;
			};
			ans += dfs(dfs, s, max - ans);
		}
		return ans;
	}
	auto getedges(int x) {
		std::vector<std::pair<int, ll>> o;
		for(auto [y, id] : e[x]) o.emplace_back(y, f[id]);
		return o;
	}
};
void matching() {
	int l, r, m;
	cin >> l >> r >> m;
	maxflow s(l + r + 1);
	for(int i = 1;i <= l;++i) s.add(0, i, 1);
	for(int i = 1;i <= r;++i) s.add(i + l, l + r + 1, 1);
	for(int i = 0, x, y;i < m;++i) {
		cin >> x >> y;
		x += 1;
		y += 1;
		s.add(x, y + l, 1);
	}
	cout << s.flow(0, l + r + 1) << '\n';
	for(int i = 1;i <= l;++i) {
		for(auto [y, f] : s.getedges(i)) {
			if(f == 0 && y > i) {
				cout << i - 1 << ' ' << y - 1 - l << '\n';
			}
		}
	}
}
void loj() {
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	maxflow g(n + 1);
	for(int i = 0, u, v, w;i < m;++i) {
		cin >> u >> v >> w;
		g.add(u, v, w);
	}
	cout << g.flow(s, t) << '\n';
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	loj();
}


