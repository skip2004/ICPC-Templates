int minrep(const std::vector<int> & s) {
	int k = 0, i = 0, j = 1, n = size(s);
	for(;k < n && i < n && j < n;) {
		if(int d = s[(i + k) % n] - s[(j + k) % n]) {
			(d > 0 ? i : j) += k + 1;
			i += i == j, k = 0;
		} else {
			++ k;
		}
	}
	return std::min(i, j);
} // rotate(s.begin(), s.begin() + minrep(s), s.end());
