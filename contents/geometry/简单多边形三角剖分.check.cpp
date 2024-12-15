// https://qoj.ac/submission/608543
#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;
 
struct p2 {
	int x, y;
	ll norm() const {
		return (ll) x * x + (ll) y * y;
	}
};
p2 r90(p2 x) { return {-x.y, x.x}; }
p2 operator + (p2 x, p2 y) { return {x.x + y.x, x.y + y.y}; }
p2 operator - (p2 x, p2 y) { return {x.x - y.x, x.y - y.y}; }
p2 operator * (p2 x, int y) { return {x.x * y, x.y * y}; }
ll operator * (p2 x, p2 y) { return (ll) x.x * y.y - (ll) x.y * y.x; }
ll operator % (p2 x, p2 y) { return (ll) x.x * y.x + (ll) x.y * y.y; }
 
bool operator == (p2 x, p2 y) {
	return x.x == y.x && x.y == y.y;
}
 
const int N = 5005;
 
ll area(p2 a, p2 b, p2 c) {
	return (b - a) * (c - a);
}
 
const ll eps = 0;
std::vector<std::array<int, 3>> triangulate(std::vector<p2> a) {
	int n = a.size();
	std::vector<int> prev(n), next(n), ear(n);
	auto in = [](p2 p, p2 a, p2 b, p2 c) {
		return area(p, a, b) >= -eps && area(p, b, c) >= -eps && area(p, c, a) >= -eps;
	};
	auto is_ear = [&](int x) {
		if(area(a[prev[x]], a[x], a[next[x]]) <= eps) return 0;
		for(int i = next[next[x]];i != prev[x];i = next[i]) 
			if(in(a[i], a[prev[x]], a[x], a[next[x]])) 
				return 0;
		return 1;
	};
	for(int i = 0;i < n;++i) {
		next[i] = (i + 1) % n, prev[(i + 1) % n] = i;
	}
	for(int i = 0;i < n;++i) {
		ear[i] = is_ear(i);
	}
	std::vector<std::array<int, 3>> ans(n - 2);
	for(int ec = 0, cur = 0;ec < n - 2;++ec) {
		for(;!ear[cur];) cur = next[cur];
		int a = prev[cur], b = cur, c = next[cur];
		ans[ec] = {a, b, c};
		next[a] = c, prev[c] = a;
		ear[a] = is_ear(a), ear[c] = is_ear(c);
		cur = next[cur];
	}
	return ans;
} // 输入逆时针
 
void solve() {
	int n;
	cin >> n;
	std::vector<p2> a(n);
	ll s = 0;
	for(int i = 0;i < n;++i) {
		cin >> a[i].x >> a[i].y;
	}
	for(int i = 2;i < n;++i) {
		s += (a[i - 1] - a[0]) * (a[i] - a[0]);
	}
	if(s < 0) rgs::reverse(a);
	auto res = triangulate(a);
	using pr = std::pair<int, int>;
	std::map<pr, int> map;
	for(auto [a, b, c] : res) {
		map[pr(a, b)] = c;
		map[pr(b, c)] = a;
		map[pr(c, a)] = b;
	}
	for(auto [_, b] : map) {
		auto [u, v] = _;
		auto A = std::make_pair(v, u);
		if(map.count(A)) {
			std::array<p2, 4> arr{a[u], a[b], a[v], a[map[A]]};
			if(area(arr[1], arr[2], arr[3]) < 0 && area(arr[3], arr[0], arr[1]) < 0) {
				cout << "Yes" << '\n';
				return ;
			}
		}
	}
	cout << "No" << '\n';
}

int main() {
	//	freopen("ex.in", "r", stdin);
	std::ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	for(int i = 0;i < t;++i) {
		solve();
	}
}


