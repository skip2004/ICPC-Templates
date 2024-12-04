#include<bits/stdc++.h>
using std::cin, std::cout;
using ll = long long;
const int N = 505;
const ll inf = 1e18;

std::vector<std::pair<int, ll>> e[N];
bool down(ll & x, ll y) { return x > y ? x = y, 1 : 0; }
auto KM(int n, int m) {
	std::vector<ll> h(n + 1), rv(m + 1);
	std::vector<int> R(m + 1);
	ll cost = 0;
	for(;;) {
		std::vector<ll> d(n + 1);
		std::vector<int> vis(n + 1), p0(n + 1), p1(m + 1);
		for(int i = 0;i <= m;++i) d[R[i]] = inf;
		std::vector<ll> min_list;
		for(int x = 0;vis[x] ^= 1;) {
			ll min = 1e18;
			for(auto [j, w] : e[x]) if(down(d[R[j]], d[x] + w - rv[j])) p0[R[j]] = j, p1[j] = x;
			for(int j = 1;j <= n;++j) if(!vis[j] && down(min, d[j] - h[j])) x = j;
			min_list.push_back(min);
		}
		assert(is_sorted(min_list.begin(), min_list.end()));
		if(d[0] >= inf / 2) break;
		for(int r = p0[0];r;r = p0[R[r]]) {
			rv[r] += d[R[r]] - d[p1[r]];
			R[r] = p1[r];
		}
		cost += d[0], h = d;
	}
	return std::tuple(cost, R, rv);
}
void TEST() {
	static std::mt19937_64 gen;
	int l = gen() % 30 + 1, r = gen() % 18 + 1;
	int b = gen() % 5 + 1;
	for(int i = 1;i <= l;++i) {
		for(int j = 1;j <= r;++j) if(gen() % b == 0) {
			e[i].emplace_back(j, ll(gen()) % (ll) 1e11);
		}
	}
	auto [cost, R, rv] = KM(l, r);
	const ll inf = 1e15;
	std::vector<ll> dp(1 << r, inf);
	dp[0] = 0;
	for(int i = 1;i <= l;++i) {
		auto g = dp;
		for(auto [j, w] : e[i]) {
			for(int k = 0;k < 1 << r;++k) if((k >> (j - 1) & 1) == 0) {
				down(g[k | 1 << (j - 1)], dp[k] + w);
			}
		}
		dp = g;
	}
	int max_match = 0;
	for(int k = 0;k < 1 << r;++k) if(dp[k] < inf / 2) {
		max_match = std::max(max_match, __builtin_popcount(k));
	}
	ll min_val = inf;
	for(int k = 0;k < 1 << r;++k) if(__builtin_popcount(k) == max_match) {
		min_val = std::min(min_val, dp[k]);
	}
	assert(cost == min_val);
	std::cerr << cost << ' ' << max_match << '\n';
	// assert(cost == * min_element(dp.begin(), dp.end()));
	std::vector<int> lv(l + 1);
	for(int j = 1;j <= r;++j) {
		if(int t = R[j]) {
			assert(!lv[t]);
			lv[t] = 1;
			int ex = 0;
			for(auto [j, w] : e[t]) {
				ex |= w == rv[j];
			}
			assert(ex);
			cost -= rv[j];
		}
	}
	assert(cost == 0);
	for(int i = 1;i <= l;++i) e[i].clear();
}
int main() {
	for(int i = 0;i < 1000000;++i) {
		TEST();
	}
	return 0;
}

