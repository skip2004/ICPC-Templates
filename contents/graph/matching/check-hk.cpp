#include<bits/stdc++.h>
using std::cin;
using std::cout;
const int N = 100005;
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
}
std::array<std::vector<int>, 3> minedgecover(int nl, int nr) {
	match(nl, nr);
	std::vector<int> l, r;
	for(int i = 1;i <= nl;++i) if(!a[i]) l.push_back(i);
	for(int i = 1;i <= nr;++i) if(a[matchr[i]]) r.push_back(i);
	return {l, r, matchl};
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int nl, nr, m;
	cin >> nl >> nr >> m;
	for(int i = 0, u, v;i < m;++i) {
		cin >> u >> v;
		e[u + 1].push_back(v + 1);
	}

	auto [l, r, res] = minedgecover(nl, nr);
	std::vector<int> okl(nl + 1), okr(nr + 1);
	for(int x : l) okl[x] = 1;
	for(int x : r) okr[x] = 1;
	for(int i = 1;i <= nl;++i) {
		if(okl[i]) continue;
		for(int x : e[i]) {
			assert(okr[x]);
		}
	}
	int cc = res.size() - count(res.begin(), res.end(), 0);
	assert(cc = l.size() + r.size());
	cout << cc << '\n';
	for(int i = 1;i <= nl;++i) if(res[i]) {
		cout << i - 1 << ' ' << res[i] - 1 << '\n';
	}
}


