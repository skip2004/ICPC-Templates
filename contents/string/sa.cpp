char s[N]; int m, rk[N * 2], sa[N], tmp[N * 2], h[N], y[N];
void Sort(){
	for(int i=1;i<=m;i++) c[i] = 0;
	for(int i=1;i<=n;i++) c[rk[i]]++;
	for(int i=1;i<=m;i++) c[i] += c[i-1];
	for(int i=n;i>=1;i--) sa[c[rk[y[i]]]--] = y[i];
}
void get_sa(){
	for(int i=1;i<=n;i++) rk[i] = s[i], y[i] = i; Sort();
	for(int k=1;k<=n;k<<=1){
		int ret = 0;
		for(int i=n-k+1;i<=n;i++) y[++ret] = i;
		for(int i=1;i<=n;i++) if(sa[i] > k) y[++ret] = sa[i] - k;
		Sort(); 
		for(int i = 1; i <= n; i++) swap(rk[i], tmp[i]); 
		rk[sa[1]] = 1; int num = 1;
		for(int i=2;i<=n;i++){
			if(tmp[sa[i]] == tmp[sa[i-1]] && tmp[sa[i]+k] == tmp[sa[i-1]+k])
				rk[sa[i]] = num;
			else rk[sa[i]] = ++num;
		} m = num;
	}
}
void get_h(){
	int k = 0;
	for(int i=1;i<=n;i++){
		if(rk[i]==1) continue;
		int j = sa[rk[i]-1]; if(k) k--;
		while(i+k<=n && j+k<=n && s[i+k]==s[j+k]) k++;
		h[rk[i]] = k;
	}
} 
