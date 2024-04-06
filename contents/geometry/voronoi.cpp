std::vector<line> cut(const std::vector<line> & o, line l) {
	std::vector<line> res;
	int n = size(o);
	for(int i = 0;i < n;++i) {
		line a = o[i], b = o[(i + 1) % n], c = o[(i + 2) % n];
		int va = check(a, b, l), vb = check(b, c, l);
		if(va > 0 || vb > 0 || (va == 0 && vb == 0)) {
			res.push_back(b);
		}
		if(va >= 0 && vb < 0) {
			res.push_back(l);
		}
	}
	if(res.size() <= 2) return {};
	return res;
} // 切凸包
line bisector(p2 a, p2 b) { return line(a.x - b.x, a.y - b.y, (b.norm() - a.norm()) / 2); }
std::vector<std::vector<line>> voronoi(std::vector<p2> p) {
	int n = p.size();
	auto b = p; shuffle(b.begin(), b.end(), gen);
	const db V = 1e5; // 边框大小，重要
	std::vector<std::vector<line>> a(n, {
		{V, 0, V * V}, {0, V, V * V},
		{-V, 0, V * V}, {0, -V, V * V},
	});
	for(int i = 0;i < n;++i) {
		for(p2 x : b) if((x - p[i]).abs() > eps) {
			a[i] = cut(a[i], bisector(p[i], x));
		}
	}
	return a;
}
