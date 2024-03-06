namespace pam {
	int ch[N][26], len[N], lk[N], rp, las, nd, top[N], d[N]; 
	void init() { rp = 0, las = nd = 1, len[1] = -1, lk[0] = 1; }
	// remember to set S[0] = * 
	int jmp(int x) { while(S[rp - len[x] - 1] != S[rp]) x = lk[x]; return x; }
	void ins(int c) {
		++ rp; int p = jmp(las);
		if(!ch[p][c]) {
			int x = ++ nd; 
			len[x] = len[p] + 2; 
			lk[x] = ch[jmp(lk[p])][c];
			ch[p][c] = x; 
			if(len[x] - len[lk[x]] == d[lk[x]]) 
				top[x] = top[lk[x]], d[x] = d[lk[x]];
			else {
				top[x] = x;
				d[x] = len[x] - len[lk[x]];
			}
		} las = ch[p][c];
	}
}
while(x) {
	if(pam :: d[x] == pam :: d[pam :: lk[x]]) { 
		// when doing dp, the position i - len[x] ~ 
		// i - (len[top[x]] + d[x]) have been updated (in i - d[x])
	}
	else // update from i - len[x]
		 // getting border : {x, top[x], d[x]}
		x = pam :: lk[pam :: top[x]];
}
