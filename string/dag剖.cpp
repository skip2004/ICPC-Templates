void build() { 
	for(int i = 2; i <= nd; i++)    
		e[lk[i]].pb(i); 
	static int q[N], d[N];
	for(int i = 1; i <= nd; i++)    
		for(int j = 0; j < 26; j++)
			if(ch[i][j]) ++ d[ch[i][j]];
	int hd = 1, tl = 0; 
	q[++ tl] = 1; 
	while(hd <= tl) {
		int x = q[hd ++];
		for(int i = 0; i < 26; i++)
			if(ch[x][i]) {
				int v = ch[x][i];
				if((-- d[v]) == 0) q[++ tl] = v; 
			}
	}
	static ll f[N], h[N];
	for(int i = tl, x; i; i--) {
		f[x = q[i]] ++; 
		for(int j = 0; j < 26; j++) 
			if(ch[x][j]) f[x] += f[ch[x][j]];
	} 
	for(int i = 1, x; i <= tl; i++) {
		h[x = q[i]] ++; 
		for(int j = 0; j < 26; j++)
			if(ch[x][j]) h[ch[x][j]] += h[x];
	}
	static int nx[N], fr[N];
	for(int i = 1; i <= nd; i++) {
		for(int j = 0; j < 26; j++)
			if(ch[i][j] && f[ch[i][j]] > f[nx[i]]) nx[i] = ch[i][j]; 
		for(int j = 0; j < 26; j++) 
			if(ch[i][j] && h[i] > h[fr[ch[i][j]]]) fr[ch[i][j]] = i; 
	}
	fr[0] = nx[0] = 0; 
	static bool vis[N];
	for(int i = 1; i <= nd; i++) {
		if(fr[nx[i]] == i) son[i] = nx[i], vis[son[i]] = 1;
	}
}

