// 抄的 https://qoj.ac/submission/1220187 
#include<bits/stdc++.h>
const int N = 1 << 18;
const int mod = 998244353;
using std::cin, std::cout;

using u64 = unsigned long long;
int rev[N], wn[N], lim, invlim;
int pow(int a, int b, int ans = 1) {
	for(;b;b >>= 1, a = (u64) a * a % mod) if(b & 1)
		ans = (u64) ans * a % mod;
	return ans;
}
void init(int len) {
	lim = 2 << std::__lg((len - 1) | 1);
	invlim = mod - (mod - 1) / lim;
	for(static int i = 1;i < lim;i += i) {
		wn[i] = 1;
		const int w = pow(3, (mod - 1) / (i * 2));
		for(int j = 1;j < i;++j) {
			wn[i + j] = (u64) wn[i + j - 1] * w % mod;
		}
	}
	rev[0] = 0;
	for(int i = 1;i < lim;++i) {
		rev[i] = rev[i >> 1] >> 1 | (i % 2 ? lim / 2 : 0);
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
				t[i + j + k] = t[k + j] + (mod - x);
				t[k + j] += x;
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
using fps = std::vector<int>;

fps comp(fps f, fps g, int n) {
	int S = 4 << std::__lg((n - 1) | 1);
	f.resize(S), g.resize(S * 2);
	for(int i = S / 2 - 1;i >= 0;--i) {
		f[i * 2] = f[i], f[i * 2 + 1] = 0;
		g[i] = g[i] ? mod - g[i] : 0;
	}
	auto dc = [&](auto dc, fps & P, fps & Q, int d, int n) {
		if(n == 1) return ;
		fps V(S * 2);
		for(int i = 0;i < S;++i) if(i & n) Q[i] = 0;
		Q[S] = 1, init(S * 2), DFT(data(Q));
		for(int i = 0;i < S;++i) V[i] = (u64) Q[i] * Q[i + S] % mod;
		init(S), IDFT(data(V)), V[0] = 0;
		dc(dc, P, V, d * 2, n / 2);
		init(S), DFT(data(P));
		for(int k = 0;k < S;++k) {
			int u = Q[k], v = Q[k + S], w = P[k];
			Q[k] = (u64) v * w % mod;
			Q[k + S] = (u64) u * w % mod;
		}
		init(S * 2), IDFT(data(Q));
		for(int i = 0;i < S;++i) P[i] = (i & n) ? 0 : Q[i + S];
	};
	dc(dc, f, g, 1, S / 2);
	f.resize(n);
	return f;
}

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	fps f(n), g(n);
	for(int i = 0;i < n;++i) cin >> f[i];
	for(int i = 0;i < n;++i) cin >> g[i];
	auto ans = comp(f, g, n);
	for(int i = 0;i < n;++i) {
		cout << ans[i] << " \n"[i == n - 1];
	}
}

