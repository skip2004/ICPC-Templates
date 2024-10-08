// HK, 左到右单向边，$O(M \sqrt{|match|})$
std::vector<int> e[N];
std::vector<int> matchl, matchr, a, p; 
std::vector<int> match(int nl, int nr) {
	matchl.assign(nl + 1, 0), matchr.assign(nr + 1, 0);
	for(;;) {
		a.assign(nl + 1, 0), p.assign(nl + 1, 0);
		static std::queue<int> Q;
		for(int i = 1;i <= nl;++i) 
			if(!matchl[i]) a[i] = p[i] = i, Q.push(i);
		int succ = 0;
		for(;Q.size();) {
			int x = Q.front(); Q.pop();
			if(matchl[a[x]]) continue;
			for(int y : e[x]) {
				if(!matchr[y]) {
					for(succ = 1;y;x = p[x])
						matchr[y] = x, std::swap(matchl[x], y);
					break;
				}
				if(!p[matchr[y]])
					Q.push(y = matchr[y]), p[y] = x, a[y] = a[x];
			}
		}
		if(!succ) break;
	}
	return matchl;
} // matchl 是左边每个点匹配的右边点编号
std::pair<std::vector<int>, std::vector<int>> minedgecover(int nl, int nr) {
	match(nl, nr);
	std::vector<int> l, r;
	for(int i = 1;i <= nl;++i) if(!a[i]) l.push_back(i);
	for(int i = 1;i <= nr;++i) if(a[matchr[i]]) r.push_back(i);
	return {l, r};
}
