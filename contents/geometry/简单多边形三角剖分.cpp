std::vector<std::array<int, 3>> triangulate(std::vector<p2> a) {
	int n = a.size();
	std::vector<int> prev(n), next(n), ear(n);
	auto in = [](p2 p, p2 a, p2 b, p2 c) {
		return area(p, a, b) >= -eps && area(p, b, c) >= -eps && area(p, c, a) >= -eps;
	};
	auto is_ear = [&](int x) {
		if(area(a[prev[x]], a[x], a[next[x]]) <= eps) return 0;
		for(int i = next[next[x]];i != prev[x];i = next[i]) 
			if(in(a[i], a[prev[x]], a[x], a[next[x]])) 
				return 0;
		return 1;
	};
	for(int i = 0;i < n;++i) {
		next[i] = (i + 1) % n, prev[(i + 1) % n] = i;
	}
	for(int i = 0;i < n;++i) {
		ear[i] = is_ear(i);
	}
	std::vector<std::array<int, 3>> ans(n - 2);
	for(int ec = 0, cur = 0;ec < n - 2;++ec) {
		for(;!ear[cur];) cur = next[cur];
		int a = prev[cur], b = cur, c = next[cur];
		ans[ec] = {a, b, c};
		next[a] = c, prev[c] = a;
		ear[a] = is_ear(a), ear[c] = is_ear(c);
		cur = next[cur];
	}
	return ans;
} // 输入逆时针
