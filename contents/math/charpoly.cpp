std::vector<int> charpoly(mat a) {
	int n = a.size();
	for(int i = 1;i < n;++i) {
		for(int j = i;j < n;++j) {
			if(a[j][i - 1]) {
				std::swap(a[i], a[j]);
				for(int k = 0;k < n;++k) std::swap(a[k][i], a[k][j]);
				break;
			}
		}
		if(!a[i][i - 1]) continue;
		int x = a[i][i - 1], inv = pow(x, mod - 2);
		for(int j = 0;j < n;++j) a[j][i] = a[j][i] * (u64)x % mod;
		for(int j = i - 1;j < n;++j) a[i][j] = a[i][j] * (u64)inv % mod;
		for(int j = i + 1;j < n;++j) {
			int z = a[j][i - 1], iz = mod - z;
			for(int k = 0;k < n;++k) a[k][i] = (a[k][i] + (u64) a[k][j] * z) % mod;
			for(int k = i - 1;k < n;++k) a[j][k] = (a[j][k] + (u64) a[i][k] * iz) % mod;
		}
	}
	mat dp(n + 1, std::vector<int>(n + 1));
	dp[0][0] = 1;
	for(int i = 0;i < n;++i) {
		int x = 1;
		for(int j = i;j >= 0;--j) {
			int y = u64(mod - x) * a[j][i] % mod;
			for(int k = 0;k <= j;++k) {
				dp[i + 1][k] = ((u64) y * dp[j][k] + dp[i + 1][k]) % mod;
			} 
			if(j) x = (u64) x * a[j][j - 1] % mod;
		}
		for(int k = 0;k <= i;++k) {
			dp[i + 1][k + 1] = (dp[i][k] + dp[i + 1][k + 1]) % mod;
		}
	}
	return dp[n];
}
