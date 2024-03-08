std::pair<int, int> approx(int p, int q, int A) {
	int x = q, y = p, a = 1, b = 0;
	for(;x > A;) {
		std::swap(x, y), std::swap(a, b);
		a -= x / y * b, x %= y;
	}
	return {x, a};
} // $q \equiv \frac{x}{a} \pmod{p}, x \leq A$, |a| 取到最小值
