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
		for(int k = i & (1 << 19);k--;) 
			if(t[k] >= mod * 9ull) t[k] -= mod * 9ull;
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
int bostan_mori(fps p, fps q, ll k) {
	int n = q.size();
	for(;k;k >>= 1) {
		auto nq = q;
		for(int i = 1;i < n;i += 2) nq[i] = mod - nq[i];
		auto u = conv(p, nq), v = conv(q, nq);
		int t = k & 1, m = (size(u) + 1 - t) / 2;
		p.resize(m);
		for(int i = 0;i < m;++i) p[i] = u[i * 2 + t];
		for(int i = 0;i < n;++i) q[i] = v[i * 2];
	}
	return pow(q[0], mod - 2, p[0]);
}
std::pair<fps, fps> convert(fps a, fps c) {
	int d = c.size();
	fps q(d + 1); q[0] = 1;
	for(int i = 0;i < d;++i) q[i + 1] = (mod - c[i]) % mod;
	fps p = conv(a, q);
	p.resize(a.size());
	return {p, q};
}
int d; ll k;
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	cin >> d >> k;
	std::cerr << d << ' ' << k << '\n';
	fps a(d), c(d);
	for(int i = 0;i < d;++i) cin >> a[i];
	for(int i = 0;i < d;++i) cin >> c[i];
	//for(int i = 0;i < d;++i) a[i] = 1;
	//for(int i = 0;i < d;++i) c[i] = 1;
	auto [p, q] = convert(a, c);
	cout << bostan_mori(p, q, k) << '\n';;

}
