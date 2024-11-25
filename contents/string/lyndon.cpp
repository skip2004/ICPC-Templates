auto duval(const std::vector<int> & s) {
	int n = s.size();
	std::vector<std::vector<int>> res;
	for(int i = 0;i < n;) {
		int j = i + 1, k = i;
		for(;j < n && s[k] <= s[j];++j) {
			if(s[k] < s[j]) {
				k = i;
			} else {
				++ k;
			}
		}
		for(;i <= k;i += j - k) {
			res.emplace_back(s.begin() + i, s.begin() + i + (j - k));
		}
	}
	return res;
}
