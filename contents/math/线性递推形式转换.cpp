std::pair<fps, fps> convert(fps a, fps c) {
	int d = c.size();
	fps q(d + 1); q[0] = 1;
	for(int i = 0;i < d;++i) q[i + 1] = norm(mod - c[i]);
	for(;q.back() == 0;) q.pop_back();
	fps p = conv(a, q);
	p.resize(a.size());
	return {p, q};
}
