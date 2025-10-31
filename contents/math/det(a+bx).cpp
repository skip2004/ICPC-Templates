std::vector<int> det(mat a, mat b) {
	int n = a.size();
	std::vector<int> ans(n+1);
	int t = 1, d = 0;
	for(int i = 0;i < n;++i) {
		for(;!b[i][i];) {
			for(int j = i + 1;j < n;++j) if(b[i][j]) {
				t = mod - t;
				for(int k = 0;k < n;++k) std::swap(a[k][i], a[k][j]), std::swap(b[k][i], b[k][j]);
				break;
			}
			if(b[i][i]) break;
			if(++d > n) return ans;
			for(int j = 0;j < n;++j) {
				b[i][j] = a[i][j], a[i][j] = 0;
			}
			for(int j = 0;j < i;++j) {
				u64 c = mod - b[i][j];
				for(int k = 0;k < n;++k) {
					a[i][k] = (a[i][k] + c * a[j][k]) % mod;
					b[i][k] = (b[i][k] + c * b[j][k]) % mod;
				}
			}
		}
		t = (u64) t * b[i][i] % mod;
		u64 inv = pow(b[i][i], mod - 2);
		for(int j = 0;j < n;++j) {
			a[i][j] = a[i][j] * inv % mod;
			b[i][j] = b[i][j] * inv % mod;
		}
		for(int j = 0;j < n;++j) if(j != i) {
			u64 c = mod - b[j][i];
			for(int k = 0;k < n;++k) {
				a[j][k] = (a[j][k] + c * a[i][k]) % mod;
				b[j][k] = (b[j][k] + c * b[i][k]) % mod;
			}
		}
	}
	auto r = charpoly(a);
	for(int i = d;i <= n;++i) ans[i - d] = u64((n - i) % 2 ? mod - t : t) * r[i] % mod;
	return ans;
}
