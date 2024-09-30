#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;
const int mod = 998244353;
int pow(int a, int b, int ans = 1) {
	for(;b;b >>= 1, a = (u64) a * a % mod) if(b & 1)
		ans = (u64) ans * a % mod;
	return ans;
}
void add(int & x, int y) {
	if((x += y) >= mod) x -= mod;
}
std::vector<int> BM(std::vector<int> a) {
	int n = size(a), len = 0, s = 1, m = 0;
	std::vector<int> res(n), lst(n), tmp;
	res[0] = 1;
	for(int i = 0;i < n;++i) {
		int d = 0; ++m;
		for(int j = 0;j <= len;++j) 
			d = (d + (u64) res[j] * a[i - j]) % mod;
		if(!d) continue;
		tmp = res;
		u64 k = pow(s, mod - 2, mod - d);
		for(int j = m;j < n;++j) res[j] = (res[j] + k * lst[j - m]) % mod;
		if(len * 2 > i) continue;
		len = i - len + 1, lst = tmp, s = d, m = 0;
	}
	std::vector<int> c(len);
	for(int i = 0;i < len;++i) c[i] = (mod - res[i + 1]) % mod;
	return c;
} // $a_n = \sum_{i=0}^{size(c)-1} c_i a_{n-1-i}$
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	if(!n) return puts("0"), 0;
	std::vector<int> f(n);
	for(int & x : f) cin >> x;
	auto res = BM(f);
	cout << size(res) << '\n';
	for(int x : res) cout << x << ' ';
}
