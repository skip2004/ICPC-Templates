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
	for(int i = m;i < n;++i) b[i] = norm(mod - c[i]);
}
void log(int * a, int * b, int n) { // b = log(a) (mod x^n)
	static int c[N], d[N];
	inv(a, c, n), init(n + n);
	for(int i = 1;i < n;++i) d[i - 1] = (u64) a[i] * i % mod;
	cpy(d, d, n - 1), cpy(c, c, n);
	DFT(c), DFT(d);
	for(int i = 0;i < lim;++i) c[i] = (u64) c[i] * d[i] % mod;
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

