std::vector<int> kmp(const std::string & s) {
	std::vector<int> b(s.size());
	for(int i = 1, j = 0;i < (int) s.size();++i) {
		for(;j && s[i] != s[j];) j = b[j - 1];
		b[i] = j += s[i] == s[j];
	}
	return b;
}
std::vector<int> match(const std::string & s, const std::string & t) {
	auto b = kmp(s);
	std::vector<int> ans;
	for(int i = 0, j = 0;i < (int) t.size();++i) {
		for(;j && t[i] != s[j];) j = b[j - 1];
		j += t[i] == s[j];
		if(j == (int) s.size()) ans.push_back(i - s.size() + 1), j = b[j - 1];
	}
	return ans;
}
