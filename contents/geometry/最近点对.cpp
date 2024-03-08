db mindist(std::vector<p2> a) {
	db ans = 1e18;
	sort(a.begin(), a.end(), [](p2 x, p2 y) { return x.x < y.x; });
	ans = (a[0] - a[1]).abs();
	auto solve = [&](auto s, int l, int r) {
		if(l + 1 == r) return ;
		int mid = (l + r) >> 1;
		db mx = a[mid].x;
		s(s, l, mid), s(s, mid, r);
		static std::vector<p2> b; b.clear();
		inplace_merge(a.begin() + l, a.begin() + mid, a.begin() + r, [](p2 x, p2 y) { return x.y < y.y; });
		for(int i = l;i < r;++i)
			if(fabs(a[i].x - mx) <= ans) b.push_back(a[i]);
		for(int i = 1;i < (int) b.size();++i) 
			for(int j = i - 1;j >= 0 && b[i].y <= b[j].y + ans;--j) ans = std::min(ans, (b[i] - b[j]).abs());
	};
	solve(solve, 0, a.size());
	return ans;
}
