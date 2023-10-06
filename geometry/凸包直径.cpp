db convex_diameter(std::vector<vec2> & o) {
	int n = size(o);
	db max = 0;
	for(int i = 0, j = 0;i < n;++i) {
		for(;j + 1 < n && (o[j] - o[i]).abs() < (o[j + 1] - o[i]).abs();) ++ j;
		max = std::max(max, (o[j] - o[i]).abs());
	}
	return max;
} // 凸包直径
