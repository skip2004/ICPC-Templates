std::vector<p2> cut(const std::vector<p2> & o, line l) {
	std::vector<p2> res;
	int n = size(o);
	for(int i = 0;i < n;++i) {
		p2 a = o[i], b = o[(i + 1) % n];
		if(sgn(l(a)) >= 0) res.push_back(a); // 注意 sgn 精度
		if(sgn(l(a)) * sgn(l(b)) < 0) res.push_back(line(a, b) & l);
	}
	return res;
} // 切凸包
