#include<bits/stdc++.h>
namespace rgs = std::ranges;
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = double;
const int N = 2 << 20;
const int mod = 998244353;
int rev[N], wn[N], lim, invlim;
int pow(int a, int b, int ans = 1) {
	for(;b;b >>= 1, a = (u64) a * a % mod) if(b & 1)
		ans = (u64) ans * a % mod;
	return ans;
}
void init(int len) {
	for(lim = 1;lim < len;lim <<= 1);
	invlim = mod - (mod - 1) / lim;
	for(static int i = 1;i < lim;i += i) {
		wn[i] = 1;
		const int w = pow(3, mod / i / 2);
		for(int j = 1;j < i;++j) {
			wn[i + j] = (u64) wn[i + j - 1] * w % mod;
		}
	}
	for(int i = 1;i < lim;++i) {
		rev[i] = rev[i >> 1] >> 1 | (i % 2u * lim / 2);
	}
}
void DFT(int * a) {
	static u64 t[N];
	for(int i = 0;i < lim;++i) t[i] = a[rev[i]];
	for(int i = 1;i < lim;i += i) {
		if(i >> 19 & 1)
			for(int k = 0;k < lim;++k) t[k] %= mod;
		for(int j = 0;j < lim;j += i + i) {
			for(int k = 0;k < i;++k) {
				const u64 x = t[i + j + k] * wn[i + k] % mod;
				t[i + j + k] = t[k + j] + (mod - x), t[k + j] += x;
			}
		}
	}
	for(int i = 0;i < lim;++i) a[i] = t[i] % mod;
}
void IDFT(int * a) {
	DFT(a), std::reverse(a + 1, a + lim);
	for(int i = 0;i < lim;++i)
		a[i] = (u64) a[i] * invlim % mod;
}
void cpy(int * a, int * b, int n) {
	if(a != b) memcpy(a, b, n << 2);
	memset(a + n, 0, (lim - n) << 2);
}
void inv(int * a, int * b, int n) { // b = inv(a) mod x^n
	if(n == 1) return void(*b = pow(*a, mod - 2));
	static int c[N], d[N];
	int m = (n + 1) / 2;
	inv(a, b, m);
	init(n + m), cpy(c, b, m), cpy(d, a, n);
	DFT(c), DFT(d);
	for(int i = 0;i < lim;++i) c[i] = (u64) c[i] * c[i] % mod * d[i] % mod;
	IDFT(c);
	for(int i = m;i < n;++i) b[i] = (mod - c[i]) % mod;
}
using fps = std::vector<int>;
fps conv(fps a, fps b) {
	static int A[N], B[N];
	init(a.size() + b.size() - 1);
	cpy(A, a.data(), a.size());
	cpy(B, b.data(), b.size());
	DFT(A), DFT(B);
	for(int i = 0;i < lim;++i) {
		A[i] = (u64) A[i] * B[i] % mod;
	}
	IDFT(A);
	return fps(A, A + a.size() + b.size() - 1);
}
int norm(int x) {
	return x >= mod ? x - mod : x;
}
fps inv(fps a, int n) {
	static int res[N];
	if(a.size() < n) a.resize(n);
	inv(a.data(), res, n);
	return fps(res, res + n);
}
fps cut(const fps & f, int d) {
	return fps(f.begin(), f.begin() + std::min((int)f.size(), d));
}
fps revp(const fps & f) { return fps(f.rbegin(), f.rend()); }
std::pair<fps, fps> polydiv(fps f, fps g) {
	int n = size(f), gd = size(g) - 1, qd = n - gd;
	if (n <= gd) return {fps(), f};
	auto F = cut(revp(f), qd);
	auto G = inv(revp(g), qd);
	fps q = revp(cut(conv(F, G), qd));
	g = conv(g, q);
	for(int i = 0;i < gd;++i) f[i] = (f[i] + mod - g[i]) % mod;
	return {q, cut(f, gd)};
}
fps solve(fps p, fps q, u64 k, int m) { 
	const int d = size(q) - 1;
	auto rec = [&](auto rec, ll k) {
		if(k == 0) return d > 0 ? fps{1} : fps();
		if(k == 1) {
			int p = pow(q[0], mod - 2); fps res(d);
			for(int i = 0;i < d;++i) res[i] = u64(mod - p) * q[i + 1] % mod;
			return res;
		}
		fps f = rec(rec, (k + 1) / 2);
		f = conv(f, f);
		if(k & 1) f.insert(f.begin(), 0);
		return polydiv(f, q).second;
	};
	fps res = rec(rec, k);
	res = polydiv(conv(res, p), q).second;
	res = conv(res, inv(q, m));
	return fps(res.begin(), res.begin() + m);
} 
fps solve_x(fps p, fps q, u64 k, int m) { 
	auto [a, p0] = polydiv(p, q);
	auto ans = p0.size() ? solve(p0, q, k, m) : fps(m);
	for(int i = 0;i < m;++i) {
		if(k + i < (int) a.size()) ans[i] = (ans[i] + a[i + k]) % mod;
	}
	return ans;
}
std::pair<fps, fps> convert(fps a, fps c) {
	int d = c.size();
	fps q(d + 1); q[0] = 1;
	for(int i = 0;i < d;++i) q[i + 1] = norm(mod - c[i]);
	for(;q.back() == 0;) q.pop_back();
	fps p = conv(a, q);
	p.resize(a.size());
	return {p, q};
}
int d, m; ll k;
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> d >> k >> m;
	std::cerr << d << ' ' << k << ' ' << m << std::endl;
	fps a(d), c(d);
	for(int i = 0;i < d;++i) cin >> a[i];
	for(int i = 0;i < d;++i) cin >> c[i];
	auto [p, q] = convert(a, c);
	auto ans = solve_x(p, q, k, m);
	for(int i = 0;i < m;++i) {
		cout << ans[i] << " \n"[i + 1 == m];
	}

}
