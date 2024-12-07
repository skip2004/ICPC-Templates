//http://106.14.32.20:17180/submission/161146
#include<bits/stdc++.h>
using std::cin, std::cout;

const int N = 100005;
std::mt19937 gen;
using u64 = unsigned long long;
int ctz(u64 x) { return __builtin_ctzll(x); }
int clz(u64 x) { return __builtin_clzll(x); }
struct ds {
	std::vector<std::vector<u64>> o;
	int d;
	ds(int s) { // [0, s]
		do o.emplace_back((s >>= 6) + 1); while(s);
		d = o.size();
	}
	void ins(int x) {
		for(int i = 0;i < d;++i) {
			u64 w = 1ull << (x & 63), & v = o[i][x >>= 6];
			if(v & w) return ;
			v |= w;
		}
	}
	void del(int x) {
		for(int i = 0;i < d;++i) {
			u64 w = 1ull << (x & 63), & v = o[i][x >>= 6];
			if(v &= ~w) return ;
		}
	}
	int next(int x) const {
		for(int i = 0;i < d;++i) {
			int b = x & 63;
			if(u64 v = o[i][x >>= 6] >> b >> 1) {
				int ans = x * 64 + ctz(v) + b + 1;
				for(int j = i - 1;j >= 0;--j)
					ans = ans * 64 + ctz(o[j][ans]);
				return ans;
			}
		}
		return -1;
	}
	int prev(int x) const {
		for(int i = 0;i < d;++i) {
			int b = x & 63;
			if(u64 v = o[i][x >>= 6] & ((1ull << b) - 1)) {
				int ans = x * 64 + (63 - clz(v));
				for(int j = i - 1;j >= 0;--j) {
					ans = ans * 64 + (63 - clz(o[j][ans]));
				}
				return ans;
			}
		}
		return -1;
	}
	int min() const {
		int ans = 0;
		for(int j = d - 1;j >= 0;--j) ans = ans * 64 + ctz(o[j][ans]);
		return ans;
	}
	int max() const {
		int ans = 0;
		for(int j = d - 1;j >= 0;--j) ans = ans * 64 + (63 - clz(o[j][ans]));
		return ans;
	}
};
int main() {
	ds t(5e6 + 1);
	std::ios::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	for(int i = 0;i < n;++i) {
		char op; int v;
		cin >> op >> v;
		if(op == '1') {
			t.ins(v);
		}
		if(op == '2') {
			t.del(v);
		}
		if(op == '3') {
			cout << t.prev(v) << '\n';
		}
		if(op == '4') {
			cout << t.next(v) << '\n';
		}
		int u = t.prev(5e6 + 1);
		assert(u == -1 || u == t.max());
		u = t.next(0);
		assert(u == -1 || u == t.min());
	}
}
