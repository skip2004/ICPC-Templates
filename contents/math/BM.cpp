std::vector<int> BM(std::vector<int> a) {
	int n = size(a), len = 0, s = 1, m = 0;
	std::vector<int> res(n), lst(n), tmp;
	res[0] = 1;
	for(int i = 0;i < n;++i) {
		int d = 0; ++m;
		for(int j = 0;j <= len;++j) 
			d = (d + (u64) res[j] * a[i - j]) % mod;
		if(!d) continue;
		tmp = res;
		u64 k = pow(s, mod - 2, mod - d);
		for(int j = m;j < n;++j) res[j] = (res[j] + k * lst[j - m]) % mod;
		if(len * 2 > i) continue;
		len = i - len + 1, lst = tmp, s = d, m = 0;
	}
	std::vector<int> c(len);
	for(int i = 0;i < len;++i) c[i] = (mod - res[i + 1]) % mod;
	return c;
}