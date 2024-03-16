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
