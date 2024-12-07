#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
const int N = 200005;
int n;
std::vector<int> e[N];
struct domtree {
	std::vector<int> dfn, p, sdom, dom, anc, min, pa;
	std::vector<std::vector<int>> b, re;
	int cc;
	void dfs0(int x) {
		dfn[x] = ++cc, p[cc] = x;
		for(int y : e[x]) {
			if(!dfn[y]) dfs0(y), pa[dfn[y]] = dfn[x];
			re[dfn[y]].push_back(dfn[x]);
		}
	}
	int find(int x) {
		int t = anc[x];
		if(anc[t] == t) return t;
		anc[x] = find(t);
		if(sdom[min[t]] < sdom[min[x]]) min[x] = min[t];
		return anc[x];
	}
	int get(int x) { return find(x), min[x]; }
	domtree() : b(n + 1), re(n + 1), cc(0) { }
	auto getdom(int s) {
		pa = dfn = p = dom = anc = std::vector<int>(n + 1);
		dfs0(s);
		for(int i = 1;i <= cc;++i) anc[i] = i;
		dom = sdom = min = anc;
		for(int i = cc;i;--i) {
			for(int w : re[i]) sdom[i] = std::min(sdom[i], sdom[get(w)]);
			if(i > 1) b[sdom[i]].push_back(i);
			for(int w : b[i]) {
				int v = get(w);
				dom[w] = sdom[v] == sdom[w] ? sdom[w] : v;
			}
			anc[i] = pa[i];
		}
		std::vector<int> ans(n + 1);
		for(int i = 1;i <= cc;++i) {
			if(dom[i] != sdom[i]) dom[i] = dom[dom[i]];
			ans[p[i]] = p[dom[i]];
		}
		return ans;
	}
};
std::vector<int> te[N];
int size[N];
void dfs0(int x, int fa = 0) {
	size[x] = 1;
	for(int y : te[x]) if(y != fa) {
		dfs0(y, x);
		size[x] += size[y];
	}
}
int main() {
#ifdef zqj
	freopen("$.in", "r", stdin);
#endif
	std::ios::sync_with_stdio(false), cin.tie(0);
	int m;
	cin >> n >> m;
	for(int i = 0, u, v;i < m;++i) {
		cin >> u >> v;
		e[u].push_back(v);
	}
	auto ans = domtree().getdom(1);
	ans[1] = 0;
	for(int i = 1;i <= n;++i) if(ans[i]) {
		te[ans[i]].push_back(i);
	}
	dfs0(1);
	for(int i = 1;i <= n;++i) {
		cout << size[i] << " \n"[i == n];
	}
//	int s;
//	cin >> n >> m >> s;
//	for(int i = 0, u, v;i < m;++i) {
//		cin >> u >> v;
//		e[u + 1].push_back(v + 1);
//	}
//	auto res = domtree().getdom(s + 1);
//	for(int i = 1;i <= n;++i) {
//		cout << res[i] - 1 << ' ';
//	}
}
