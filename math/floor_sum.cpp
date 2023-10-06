u64 floor_sum(u64 n, u64 m, u64 a, u64 b) {
	u64 ans = 0;
	for(;;) {
		if(a >= m) {
			ans += n * (n - 1) / 2 * (a / m);
			a %= m;
		}
		if(b >= m) {
			ans += n * (b / m);
			b %= m;
		}
		u64 ymax = a * n + b;
		if(ymax < m) break;
		n = ymax / m;
		b = ymax % m;
		std::swap(m, a);
	}
	return ans;
}
