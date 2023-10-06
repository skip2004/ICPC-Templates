std::vector<int> Zalgo(const std::string & s) {
	std::vector<int> lcp(s.size());
	lcp[0] = s.size();
	for(int i = 1, l = 0, r = 0;i < (int) s.size();++i) {
		int & x = lcp[i];
		if(i < r) x = std::min(lcp[i - l], r - i);
		for(;i + x < (int) s.size() && s[x] == s[i + x];)
			++ x;
		if(i + x > r) l = i, r = i + x;
	}
	return lcp;
}
