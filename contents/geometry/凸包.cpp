db cross(p2 x, p2 y, p2 z) { return (y.x - x.x) * (z.y - x.y) - (y.y - x.y) * (z.x - x.x); }
std::vector<p2> gethull(std::vector<p2> o) {
	rgs::sort(o, [](p2 x, p2 y) { return eq(x.x, y.x) ? x.y < y.y : x.x < y.x; });
	o.erase(unique(o.begin(), o.end(), [](p2 x, p2 y) {
		return eq(x.x, y.x) && eq(x.y, y.y);
	}), o.end());
	std::vector<p2> s;
	for(int i = 0;i < (int) o.size();++i) {
		for(;s.size() >= 2 && cross(s.rbegin()[1], s.back(), o[i]) <= eps;)
			s.pop_back();
		s.push_back(o[i]);
	}
	for(int i = o.size() - 2, t = s.size();i >= 0;--i) {
		for(;s.size() > t && cross(s.rbegin()[1], s.back(), o[i]) <= eps;)
			s.pop_back();
		s.push_back(o[i]);
	}
	if(s.size() > 1) s.pop_back();
	return s;
} // 把两个 eps 改成 -eps 可求出所有在凸包上的点
int findmin(std::vector<p2> & a, auto cmp) {
	int l = 0, r = a.size() - 1, d = 1;
	if(cmp(a.back(), a[0])) std::swap(l, r), d = -1;
	for(;(r - l) * d > 1;) {
		int mid = (l + r) >> 1;
		if(cmp(a[mid], a[mid - d]) && cmp(a[mid], a[l])) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return l;
} // cmp is less, and a.size()>0 plz
int contains(std::vector<p2> & a, p2 x) {
	auto it = lower_bound(a.begin() + 2, a.end(), x, [&](p2 x, p2 y) {
		return cross(a[0], x, y) > 0;
	});
	ll c0 = cross(it[-1], *it, x), c1 = cross(a[0], a[1], x);
	if(it != a.end() && c0 >= 0 && c1 >= 0) {
		return c0 > 0 && c1 > 0 && cross(a.back(), a[0], x) > 0 ? IN : ON;
	} else {
		return 0;
	}
} // a.size()>2 plz
