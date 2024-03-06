db findmax(db a, db c, auto f) {
	auto g = [&](db l, db r) {
		return l + (r - l) * (std::numbers::phi_v<db> - 1);
	};
	db b = g(a, c), bv = f(b);
	for(int i = 0;i < 45;++i) {
		db x = g(a, b), xv = f(x);
		if(xv > bv) { // change here if findmin
			c = b, b = x, bv = xv;
		} else {
			a = c, c = x;
		}
	}
	return bv;
} // $\log_{1.618}(2) \approx 1.44$
