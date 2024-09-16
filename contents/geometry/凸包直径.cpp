db convex_diameter(std::vector<p2> & o) {
	int n = size(o);
	db max = 0;
	for(int i = 0, j = 1 % n;i < j;++i) {
		for(;;j = (j + 1) % n) {
			max = std::max(max, (o[j] - o[i]).abs());
			if((o[i + 1] - o[i]) * (o[(j + 1) % n] - o[j]) <= 0) break;
		}
	}
	return max;
} // 凸包直径，不能有三点共线
