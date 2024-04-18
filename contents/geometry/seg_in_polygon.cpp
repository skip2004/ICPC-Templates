bool contains(p2 x, p2 y, const std::vector<p2> & a) {
	using pr = std::pair<double, int>;
	std::vector<pr> e = {pr(-inf, 0), pr(inf, 0)};
	p2 t = y - x;
	auto f = [&](p2 a, p2 b, p2 c, p2 d) {
		return (b - a).abs() * ((c - a) * (d - c)) / ((b - a) * (d - c));
	};
	for(int i = 0;i < (int) a.size();++i) {
		p2 u = a[i], v = a[(i + 1) % a.size()];
		int a = sgn(t * (u - x));
		int b = sgn(t * (v - x));
		if(a != b) e.emplace_back(f(x, y, u, v), b - a);
	}
	sort(e.begin(), e.end());
	int sum = 0; db R = t.abs();
	for(int i = 0;i + 1 < (int) e.size();++i) {
		sum += e[i].second;
		if(sum == 0 && std::max(e[i].first, 0.) + eps < std::min(e[i + 1].first, R)) {
			return 0;
		}
	}
	return 1;
}
