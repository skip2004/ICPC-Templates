char s[N];
int rank[N], sa[N], h[N], n, L;
bool cmp(int a, int b) {
	if(rank[a] != rank[b]) return rank[a] < rank[b];
	return b + L <= n && (a + L > n || rank[a + L] < rank[b + L]);
}
void SA() { // s[n + 1] need '0'
	static int a[N], t[N];
	for(int i = 1;i <= n;++i) rank[i] = s[i];
	std::iota(a, a + n + 1, 0);
	for(L = 1;;L <<= 1) {
		std::sort(a + 1, a + n + 1, cmp);
		for(int i = 1, r = 0;i <= n;++i) t[a[i]] = r += !i || cmp(a[i - 1], a[i]);
		memcpy(rank + 1, t + 1, n << 2);
		if(t[a[n]] == n) break;
	}
	for(int i = 1;i <= n;++i) sa[rank[i]] = i;
	for(int i = 1, k = 0;i <= n;++i) if(rank[i] < n) {
		int j = sa[rank[i] + 1];
		for(k -= !!k;s[i + k] == s[j + k];++k);
		h[rank[i]] = k;
	}
}
