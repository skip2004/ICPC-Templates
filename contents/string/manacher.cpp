std::vector<int> manacher(const std::string & s, bool is_even) {
	const int N = s.size() - is_even;
	std::vector<int> o(N); // 半径
	for(int i = 0, mid = 0, r = 0;i < N;++i) {
		int & x = o[i] = 0;
		if(i < r) x = std::min(r - i, o[mid - i]);
		for(;i - x >= 0 && i + x < N && s[i - x] == s[i + x + is_even];)
			++ x;
		if(i + x > r) {
			mid = i * 2;
			r = i + x;
		}
	}
	return o;
}
