#include<bits/stdc++.h>
using std::cin;
using std::cout;
using u64 = unsigned long long;
const int mod = 998244353;
const int N = 1 << 20;
int rev[N], wn[N], lim, invlim;
int pow(int a, int b, int ans = 1) {
    for(;b;b >>= 1, a = (u64) a * a % mod) if(b & 1)
        ans = (u64) ans * a % mod;
    return ans;
}
void init(int len) {
    lim = 2 << std::__lg(len - 1);
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
    for(int i = 0;i < lim;++i) {
        t[i] = a[rev[i]];
    }
    for(int i = 1;i < lim;i += i) {
        for(int j = 0;j < lim;j += i + i) {
            for(int k = 0;k < i;++k) {
                const u64 x = t[i + j + k] * wn[i + k] % mod;
                t[i + j + k] = t[k + j] + mod - x, t[k + j] += x;
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
    memcpy(a, b, n << 2);
    memset(a + n, 0, (lim - n) << 2);
}
int norm(int x) {
	return x >= mod ? x - mod : x;
}
void inv(int * a, int * b, int n) { // b = a^-1 (mod x^n)
    if(n == 1) return void(*b = pow(*a, mod - 2));
    static int c[N], d[N];
    int m = (n + 1) / 2;
    inv(a, b, m);
    init(n + m), cpy(c, b, m), cpy(d, a, n);
    DFT(c), DFT(d);
    for(int i = 0;i < lim;++i) c[i] = (u64) c[i] * c[i] % mod * (mod - d[i]) % mod;
    IDFT(c);
    for(int i = m;i < n;++i) b[i] = c[i];
}
void log(int * a, int * b, int n) { // b = log(a) (mod x^n)
    static int c[N], d[N];
    inv(a, c, n), init(n + n);
    for(int i = 1;i < n;++i) d[i - 1] = (u64) a[i] * i % mod;
    cpy(d, d, n - 1), cpy(c, c, n);
    DFT(c), DFT(d);
	for(int i = 0;i < lim;++i) {
		c[i] = (u64) c[i] * d[i] % mod;
	}
    IDFT(c), *b = 0;
    for(int i = 1;i < n;++i) b[i] = pow(i, mod - 2, c[i - 1]);
}
void exp(int * a, int * b, int n) { // b = e^a (mod x^n)
	if(n == 1) return void(*b = 1);
	int m = (n + 1) / 2;
	memset(b, 0, n << 2);
	exp(a, b, m);
	static int c[N], d[N];
	log(b, c, n);
	for(int i = 0;i < n;++i) {
		c[i] = (a[i] + mod - c[i]) % mod;
	}
	init(n);
	cpy(d, b, m), DFT(d);
	cpy(c, c, n), DFT(c);
	for(int i = 0;i < lim;++i) {
		c[i] = (u64) c[i] * d[i] % mod;
	}
	IDFT(c);
	memcpy(b + m, c + m, (n - m) << 2);
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int n;
	cin >> n;
	static int a[N], b[N], c[N], d[N];
	for(int i = 0;i < n;++i) {
		cin >> a[i];
	}
	n *= 2;
	exp(a, b, n);
	exp(a, b, n);
	for(int i = 0;i < n / 2;++i) {
		cout << b[i] << ' ';
	}

}

