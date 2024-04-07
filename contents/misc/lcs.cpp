int lim;
struct bitset {
	static const int B = 63;
	u64 a[N / B + 1];
	void set(int p) { a[p / B] |= 1ull << (p % B); }
	bool test(int p) { return a[p / B] >> (p % B) & 1; }
	void run(const bitset & o) {
		u64 c = 1;
		for(int i = 0;i < lim;++i) {
			u64 x = a[i], y = x | o.a[i];
			x += x + c + (~y & (1ull << 63) - 1);
			a[i] = x & y, c = x >> 63;
		}
	}
} dp;
