using cp = std::complex<ll>;
cp fracBS(ll n, ll m, auto f) {
	bool dir = 1, A = 1, B = 1;
	cp lo(0, 1), hi(1, 1); // hi can be (1, 0), f(hi) must be true
	if (f(lo)) return lo;
	while(A || B) {
		ll adv = 0, s = 1;
		for (int x = 0;s;(s *= 2) >>= x) {
			adv += s;
			cp mid = lo * adv + hi;
			if (mid.real() > n || mid.imag() > m || dir == !f(mid)) {
				adv -= s, x = 2;
			}
		}
		hi += lo * adv, dir = !dir;
		swap(lo, hi);
		A = B, B = adv;
	}
	return dir ? hi : lo;
} // 返回值是最小的使得 f 为真的
  // 另外一个是最大的使得 f 为假的
