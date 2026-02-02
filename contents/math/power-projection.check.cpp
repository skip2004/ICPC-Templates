// 抄的 https://qoj.ac/submission/1220187 
#include<bits/stdc++.h>
const int N = 1 << 20;
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

fps conv(fps a, fps b) {
	int d = a.size() + b.size() - 1;
	init(d);
	a.resize(lim); b.resize(lim);
	DFT(a.data()), DFT(b.data());
	for(int i = 0;i < lim;++i) a[i] = (u64) a[i] * b[i] % mod;
	IDFT(a.data());
	return fps(a.begin(), a.begin() + d);
}
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

using fps = std::vector<int>;
using ll = long long;

// Power Projection: [x^(n-1)] f(x) g(x)^i, i = 0..n-1
// require g(0) = 0
fps PowerProjection(fps f, fps g, int n) {
	int m = 2 << std::__lg((n - 1) | 1), S = m * 2;
	reverse(f.begin(), f.end());
	f.insert(f.begin(), m + S, 0);
	f.resize(S * 2);
	g.resize(S * 2);
	for (int i = 0; i < m; ++i) g[i] = g[i] ? mod - g[i] : 0;
	for(;m > 1;m /= 2) {
		for(int i = 0;i < S * 2;++i) (i & m ? g[i] : f[i]) = 0;
		for(int i = 0;i < S;++i) g[i + S] = 0, f[i] = 0;
		g[S] = 1, init(S * 2), IDFT(f.data()), DFT(g.data());
		for (int i = 0; i < S; ++i) {
			u64 a = f[i], b = f[i + S];
			u64 c = g[i], d = g[i + S];
			f[i + S] = (a * d + b * c) % mod;
			g[i] = (u64)c * d % mod;
		}
		init(S), DFT(f.data() + S), IDFT(g.data()), g[0] = 0;
	};
	for(int i = 0;i < n;++i) f[i] = f[i * 2 + 1 + S];
	f.resize(n);
	return f;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::mt19937 gen;
	for(int tc = 0;tc < 100000;++tc) {
		int n = gen() % 200 + 1;
		fps f(n), g(n);
		for(int i = 0;i < n;++i) {
			f[i] = gen() % mod;
			g[i] = gen() % mod;
		}
		g[0] = 0;
		auto ans = PowerProjection(f, g, n);
		fps std;
		for(int i = 0;i < n;++i) {
			std.push_back(f[n - 1]);
			f = conv(f, g), f.resize(n);
		}
		assert(std == ans);
		if(tc % 1000 == 0)
		std::cerr << "testcase : " << tc << ' ' << "passed!\n";
	}
}


