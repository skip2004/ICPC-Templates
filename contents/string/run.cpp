// need lcp and lcs 
bool cmp(int x, int y){
	int l = lcp(x, y);
	if(x + l > n) return true; 
	if(y + l > n) return false; 
	return S[x + l] < S[y + l];
}
set <pi> ex; 
void ins(int l, int r) {
    int p = r - l;
    int l1 = lcp(l, r);
    int l2 = lcs(l - 1, r - 1);
    int L = l - l2, R = r + l1 - 1; 
    if(R - L + 1 >= 2 * p) {
        auto iter = ex.lower_bound(pi(L, R));
        if(iter != ex.end() && *iter == pi(L, R)) return ;
        ex.emplace_hint(iter, pi(L, R));
        runs.pb((run){L, R, p}); 
    }
}
void Run(int o){
	static int s[N];
	int top = 0; s[++top] = n + 1; 
	for(int i = n; i; i--){
		while(top > 1 && cmp(i, s[top]) == o) --top;
		ins(i, s[top]), s[++top] = i; 
	}
}
