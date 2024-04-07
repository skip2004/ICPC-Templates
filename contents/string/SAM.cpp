void init() {
	nd = las = 1; 
}
void extend(int c, int k) {
	int x = ++ nd, p = las; las = x;
	len[x] = len[p] + 1, r[x] = k, ed[k] = x; 
	for(; p && !ch[p][c]; p = lk[p]) ch[p][c] = x;   
	if(!p) return lk[x] = 1, void();
	int q = ch[p][c];
	if(len[q] == len[p] + 1)
		return lk[x] = q, void();
	int cl = ++ nd;
	r[cl] = r[q];
	len[cl] = len[p] + 1; 
	memcpy(ch[cl], ch[q], 104);
	lk[cl]= lk[q], lk[q] = lk[x] = cl;
	for(; p && ch[p][c] == q; p = lk[p]) ch[p][c] = cl;
} // ex - sam, trie + bfs 
void build() {
	static int bin[N];
	memset(bin, 0, sizeof (int) * (n + 1));
	for(int i = 1; i <= nd; i++) ++ bin[len[i]];
	for(int i = 1; i <= n; i++) bin[i] += bin[i - 1];
	for(int i = nd; i; i--) A[bin[len[i]]--] = i; 
}