struct seg {
	ll o[1 << 20]; int L;
	void upt(int x) {
		o[x] = o[x << 1] + o[x << 1 | 1];
	}
	void init(int n, int * w) {
		L = 2 << std::__lg(n + 1);
		for(int i = 1;i <= n;++i) o[i + L] = w[i];
		for(int i = L;i >= 1;--i) upt(i);
	}
	void upt(int p, int v) {
		for(o[p += L] += v;p >>= 1;upt(p));
	}
	ll qry(int l, int r) {
		l += L - 1, r += L + 1;
		ll ans = 0;
		for(;l ^ r ^ 1;l >>= 1, r >>= 1) {
			if((l & 1) == 0) ans += o[l ^ 1];
			if((r & 1) == 1) ans += o[r ^ 1];
		}
		return ans;
	}
	ll qry2(int l, int r) {
		if(l == r) return o[l + L];
		ll le = o[l + L], ri = o[r + L];
		l += L, r += L;
		for(;l ^ r ^ 1;l >>= 1, r >>= 1) {
			if((l & 1) == 0) le = le + o[l ^ 1];
			if((r & 1) == 1) ri = o[r ^ 1] + ri;
		}
		return le + ri;
	}
} sgt;
