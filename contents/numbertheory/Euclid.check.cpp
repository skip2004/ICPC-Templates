//https://loj.ac/s/2042356 
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
// 万欧
// 前提 : r < q, r >= q 先提几个 U 出来再用
// 使用：Y * q <= X * p + r, 斜率 p/q, U表示向上，R表示到达一个顶点，先一些 U 再一个 R
template<class T>
T power(T a, ll k) {
	// 有效率需求可以改为半群乘法
	if(!k) return T();
	T res = a;
	for(--k;k;) {
		if(k & 1) res = res + a;
		if(k >>= 1) a = a + a;
	}
	return res;
}
template<class T>
T solve(ll p, ll q, ll r, ll l, T U, T R) {
	if (p >= q)
		return solve(p % q, q, r, l, U, power(U, p / q) + R);
	ll m = ((__int128)p * l + r) / q;
	if (!m) return power(R, l);
	ll cnt = l - ((__int128)q * m - r - 1) / p;
	return power(R, (q - r - 1) / p) + U + solve(q, p, (q - r - 1) % p, m - 1, R, U) + power(R, cnt);
}
const int N = 20;
const int mod = 998244353;
using u64 = unsigned long long;
struct mat {
	int a[N][N];
	mat() {
		memset(a, 0, sizeof(a));
	}
	mat operator * (mat y) const {
		mat res;
		for(int i = 0;i < N;++i) {
			for(int j = 0;j < N;++j) {
				for(int k = 0;k < N;++k) {
					res.a[i][k] = (res.a[i][k] + (u64) a[i][j] * y.a[j][k]) % mod;
				}
			}
		}
		return res;
	}
	mat operator + (mat y) {
		for(int i = 0;i < N;++i) {
			for(int j = 0;j < N;++j) {
				y.a[i][j] = (y.a[i][j] + a[i][j]) % mod;
			}
		}
		return y;
	}
} A, B, I;
struct TAG {
	mat L, R, sum;
	std::string debug;
	TAG() : L(I), R(I), sum() {}
	TAG(mat a, mat b, mat c, auto d) : L(a), R(b), sum(c), debug(d) {
	}
} U, R;
TAG operator + (TAG x, TAG y) {
	return {y.L * x.L, x.R * y.R, (x.sum + x.L * y.sum * x.R), x.debug + y.debug};
}

ll p, q, r, l;
int main() {
	int n;
	cin >> p >> q >> r >> l >> n;
	for(int i = 0;i < n;++i) {
		I.a[i][i] = 1;
	}
	for(int i = 0;i < n;++i) {
		for(int j = 0;j < n;++j) {
			cin >> A.a[i][j];
		}
	}
	for(int i = 0;i < n;++i) {
		for(int j = 0;j < n;++j) {
			cin >> B.a[i][j];
		}
	}
	U = {I, B, mat(), ""};
	R = {A, I, I, ""};
	auto res = solve(p, q, r, l, U, R);
	// cout << res.debug << '\n';
	mat ans = A * res.sum;
	for(int i = 0;i < n;++i) {
		for(int j = 0;j < n;++j) {
			cout << ans.a[i][j] << " \n"[j == n - 1];
		}
	}
}
