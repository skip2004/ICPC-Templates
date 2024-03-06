// 后缀加，前缀求和
struct BIT {
	ll a[N], b[N];
	void add(ll p, int v) {
		for(int i = p;i < N;i += i & -i) 
			a[i] += v, b[i] += p * v;
	}
	ll qry(ll p) {
		ll res = 0;
		for(int i = p;i;i &= i - 1) res += (p + 1) * a[i] - b[i];
		return res;
	}
	void add(int l, int r, int v) { add(l, v), add(r + 1, -v); }
	ll qry(int l, int r) { return qry(r) - qry(l - 1); }
} bit;
