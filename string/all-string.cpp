// SAM 
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
}
void init() {
	static int bin[N];
	memset(bin, 0, sizeof (int) * (n + 1));
	for(int i = 1; i <= nd; i++) ++ bin[len[i]];
	for(int i = 1; i <= n; i++) bin[i] += bin[i - 1];
	for(int i = nd; i; i--) A[bin[len[i]]--] = i; 
}
// 基本子串字典
for(int i = 2; i <= T[0].nd; i++) {
	int x = T[0].A[i];
	int R = T[0].r[x], L = R - T[0].len[x] + 1; 
	int y = T[1].fnd(T[1].ed[L], R - L + 1);
	if(T[1].len[y] == R - L + 1) {
		++ cnt; T[0].tag[x] = cnt; T[1].tag[y] = cnt; 
		rt[0][cnt] = x, rt[1][cnt] = y; 
	}
}
for(int o = 0; o < 2; o++)
for(int i = T[o].nd; i > 1; i--) {
	int x = T[o].A[i];
	if(T[o].tag[x]) continue;
	for(int k = 0; k < 26; k++)
		if(T[o].ch[x][k]) T[o].tag[x] = T[o].tag[T[o].ch[x][k]];
}
for(int o = 0; o < 2; o++)
for(int i = 2; i <= T[o].nd; i++) {
	int x = T[o].A[i];
	vec[o][T[o].tag[x]].pb(x);
}
int x = T[0].fnd(T[0].ed[r], r - l + 1);
int blk = T[0].tag[x];
// distance to the right , 0 - base 
int rp = T[0].r[rt[0][blk]] - T[0].r[x];
// distance to the up // the upper - right point is (T[0].r[rt] - T[0].len[rt] + 1, T[0].r[rt]) 
int lp = T[0].r[x] - (r - l) - (T[0].r[rt[0][blk]] - T[0].len[rt[0][blk]] + 1);

// dag 剖
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
// exKMP
static int lcp[N]; 
int mx=1, pt=1; lcp[1]=n;
for(int i=2; i<=n; i++){
	if(i<=mx) lcp[i]=min(lcp[i-pt+1],mx-i+1);
	while(i+lcp[i]<=n && S[i+lcp[i]]==S[1+lcp[i]]) ++lcp[i];
	if(i+lcp[i]-1>mx) pt=i, mx=i+lcp[i]-1;
} 
// log 个最小后缀
for(int i = 1; i <= n; i ++) {
	St.pb(i); vector<int> nw;
	for(auto t : St) {
		bool ok = true;
		while(!nw.empty()){
			int x = nw.back();
			if(S[i] > S[i-t+x]) ok = false;
			if(S[i] >= S[i-t+x]) break; nw.pop_back();
		} 
		if(ok && (nw.empty() || (i-t<=t-nw.back()))) nw.pb(t);
	} St = nw;
}
for(int x : St){
	bool FLAG = true;
	while(nx.size()){
		int y = nx.back(); int lcp = LCP(x, y); if(x + lcp - 1 >= r) break;
		if(S[x + lcp] > S[y + lcp]){ FLAG = false; break; } nx.pop_back();
	} if(FLAG && (nx.empty() || r - x + 1 <= x - nx.back())) nx.pb(x);
}
// SA 
void Sort(){
	for(int i=1;i<=m;i++) c[i] = 0;
	for(int i=1;i<=n;i++) c[rk[i]]++;
	for(int i=1;i<=m;i++) c[i] += c[i-1];
	for(int i=n;i>=1;i--) SA[c[rk[y[i]]]--] = y[i];
}
void get_SA(){
	for(int i=1;i<=n;i++) rk[i] = s[i], y[i] = i;
	Sort();
	for(int k=1;k<=n;k<<=1){
		int ret = 0;
		for(int i=n-k+1;i<=n;i++) y[++ret] = i;
		for(int i=1;i<=n;i++) if(SA[i] > k) y[++ret] = SA[i] - k;
		Sort(); swap(rk,tmp); rk[SA[1]] = 1; int num = 1;
		for(int i=2;i<=n;i++){
			if(tmp[SA[i]] == tmp[SA[i-1]] && tmp[SA[i]+k] == tmp[SA[i-1]+k])
				rk[SA[i]] = num;
			else rk[SA[i]] = ++num;
		} m = num;
	}
}
void get_h(){
	int k = 0;
	for(int i=1;i<=n;i++){
		if(rk[i]==1) continue;
		int j = SA[rk[i]-1]; if(k) k--;
		while(i+k<=n && j+k<=n && s[i+k]==s[j+k]) k++;
		h[rk[i]] = k;
	}
} 
// PAM
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
// Manachar 
S[1] = '%';
for(int i = 1; i <= len; i++){
	S[i << 1] = '&'; 
	S[i << 1|1] = s[i];
} 
len = len << 1 | 1;
S[++len] = '&';
S[++len] = '$';
int mx = 0, id = 0, ans = 0;
for(int i = 1; i <= len; i++){
	if(mx > i) p[i] = min(p[id * 2 - i], mx - i);
	else p[i] = 1;
	while(S[i - p[i]] == S[i + p[i]]) ++p[i];
	if(i + p[i] > mx) id = i, mx = i + p[i];
	ans = max(ans, p[i] - 1);
}
// Lyndon 
for(int i=1; i<=n;) {
	int j=i, k=i+1;
	while(S[j]<=S[k]){
		if(S[j]==S[k]) ++j;
		else j=i; ++k;
	}
	while(i<=j){
		printf("%d ",i+k-j-1);
		i+=k-j;
	}
} 
// Run
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
