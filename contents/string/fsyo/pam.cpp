namespace pam{
	int ch[N][26], len[N], lk[N];
	int rp, las, nd;
	void init(){
		for(int i=0; i<=nd; i++)
			len[i] = lk[i] = trs[i] = 0,
				memset(ch[i],0,sizeof(ch[i]));
		rp = 0; las = nd = 1;
		len[1] = -1; lk[0] = 1;
	} 
	int jmp(int x){ while(S[rp-len[x]-1] != S[rp]) x=lk[x]; return x; }
	void extend(int c){
		++rp; int p = jmp(las);
		if(!ch[p][c]){
			len[++nd] = len[p] + 2;
			lk[nd] = ch[jmp(lk[p])][c]; 
			ch[p][c] = nd;
		} las = ch[p][c];
	}
}
