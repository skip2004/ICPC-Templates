void init() {
	queue <int> q; 
	for(int i = 0; i < 26; i++) 
		if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		e[lk[x]].pb(x);
		for(int i = 0; i < 26; i++) {
			if(ch[x][i]) {
				lk[ch[x][i]] = ch[lk[x]][i];
				q.push(ch[x][i]);
			}
			else ch[x][i] = ch[lk[x]][i];
		}
	}
}
