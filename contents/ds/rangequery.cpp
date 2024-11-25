template<class T> struct rq {
	std::vector<std::vector<info>> v; // change type here
	T op;
	rq(auto & a, T op) : v(1, a), op(op) {
		int n = a.size();
		for(int d = 2;d < n;d += d) {
			auto & o = v.emplace_back(a);
			for(int j = d;j < n;j += d + d) {
				for(int k = 1;k < d;++k) {
					if(j + k < n) o[j + k] = op(o[j + k - 1], o[j + k]);
					o[j - k - 1] = op(o[j - k - 1], o[j - k]);
				}
			}
		}
	}
	auto query(int l, int r) {
		if(l == r) return v[0][l];
		const int lg = std::__lg(l ^ r);
		return op(v[lg][l], v[lg][r]);
	}
};
