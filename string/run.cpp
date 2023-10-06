bool cmp(int x, int y){
	int l = lcp(x, y);
	if(x + l > n) return true; 
	if(y + l > n) return false; 
	return S[x + l] < S[y + l];
}
map<pi, int> ex; 
void ins(int l, int r){
	int p = r - l;
	int l1 = lcp(l, r);
	int l2 = lcs(l - 1, r - 1);
	int L = l - l2, R = r + l1 - 1;
	if(ex[pi(L, R)]) return;
	ex[pi(L, R)] = true;
	if(R - L + 1 >= 2 * p) 
		t[++k] = (run){L, R, p};
}
void Run(int o){
	static int s[N];
	int top = 0; s[++top] = n + 1; 
	for(int i = n; i; i--){
		while(top > 1 && cmp(i, s[top]) == o) --top;
		ins(i, s[top]), s[++top] = i; 
	}
}
