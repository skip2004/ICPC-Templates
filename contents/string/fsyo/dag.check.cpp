// https://uoj.ac/submission/684817
#include <bits/stdc++.h> 
#define cs const
#define pb push_back
using namespace std; 
typedef long long ll;
typedef unsigned long long ull; 
typedef pair <int, int> pi;
#define fi first
#define se second 

namespace io {
cs int rlen = 1 << 22 | 1;
inline char gc() {
	static char buf[rlen], *p1, *p2;
	(p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, rlen, stdin));
	return p1 == p2 ? EOF : *p1++;
}
int gi() {
	int x = 0; char c = gc();
	while(!isdigit(c)) c = gc();
	while(isdigit(c)) x = (((x << 2) + x) << 1) + (c ^ 48), c = gc();
	return x;  
}
} using namespace io;


cs int N = 1e6 + 5; 

int n, m, f[N];
char str[N];
int lp[N], sp[N];
ull H[N], pw[N]; 

vector <pi> q[N];
vector <ull> ha[N];
int sz[N];
int son[N], dfn[N], top[N], pos[N];
ll ans[N];

vector <int> e[N];


namespace bit {
ll c[N];
void upt(int x, int w) {
    for(; x <= dfn[0]; x += x & -x) 
        c[x] += w; 
}
ll ask(int x) {
    ll w = 0; 
    for(; x; x -= x & -x)
        w += c[x];
    return w; 
} 
}

namespace SAM {

int ch[N][26], lk[N], len[N],  nd = 1, las = 1; 
void ins(int c) {
    int u = ++ nd, p = las; las = nd; 
    len[u] = len[p] + 1, sz[u] = 1; 
    for(; p && !ch[p][c]; p = lk[p]) ch[p][c] = u; 
    if(!p) return lk[u] = 1, void();
    int q = ch[p][c];
    if(len[q] == len[p] + 1) return lk[u] = q, void();
    int cl = ++ nd; 
    len[cl] = len[p] + 1; 
    memcpy(ch[cl], ch[q], 104);
    lk[cl] = lk[q];
    for(; p && ch[p][c] == q; p = lk[p]) ch[p][c] = cl; 
    lk[u] = lk[q] = cl;
}

void dfs_dag(int x, int tp, ull has) {
    pos[dfn[x] = ++ dfn[0]] = x, top[x] = tp, ha[tp].pb(has);
    if(!son[x]) return; 
    int c = 0; 
    for(int i = 0; i < 26; i++)
        if(ch[x][i] == son[x]) c = i; 
    dfs_dag(son[x], tp, has * pw[1] + c);
}

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
    for(int i = 1; i <= nd; i++)
        if(!vis[i]) dfs_dag(i, i, 0);
}


}

void pre_dfs(int u) {
    for(int x : e[u]) pre_dfs(x), sz[u] += sz[x];
}
void work(int u) {
    if(u > 1) bit :: upt(dfn[u], f[sz[u]]);
    //cout << "work " << u << endl; 
    for(pi qu : q[u]) {
        int l = qu.fi, r = sp[u], c = qu.se; 
        int ps = 1, len = l; 
        ll sum = 0; 
        while(len <= r) {
            int tp = top[ps];
            int cur_pos = dfn[ps] - dfn[tp]; 
            int sz = ha[tp].size(); 
            int L = 0, R = min(sz - cur_pos - 1, r - len + 1); 
            while(L < R) {
                int mid = (L + R + 1) >> 1; 
                if(ha[tp][cur_pos + mid] - ha[tp][cur_pos] * pw[mid]
                    == H[len + mid - 1] - H[len - 1] * pw[mid]) L = mid;
                else R = mid - 1; 
            }
            sum += bit :: ask(dfn[ps] + L) - bit :: ask(dfn[ps] - 1);
            ps = pos[dfn[ps] + L]; 
            len += L; 
            int v = SAM :: ch[ps][str[len] - 'a'];
            if(!v || len > r) break;
            ps = v, ++ len; 
            if(len > r) 
                sum += bit :: ask(dfn[ps]) - bit :: ask(dfn[ps] - 1);
        }
        ans[c] = sum; 
    }   
    for(int x : e[u]) work(x);
    if(u > 1) bit :: upt(dfn[u], -f[sz[u]]);
}
int main() {
    #ifdef FSYo
    freopen("1.in", "r", stdin);
    #endif
    cin >> n >> m; 
    scanf("%s", str + 1);
    
    for(int i = 1; i <= n; i++) 
        SAM :: ins(str[i] - 'a'), lp[i] = SAM :: las, sp[SAM :: las] = i;

    for(int i = 1; i <= n; i++) f[i] = gi();
    
    pw[0] = 1; 
    for(int i = 1; i <= n; i++) 
        H[i] = H[i - 1] * 223 + str[i] - 'a', pw[i] = pw[i - 1] * 223; 
    
    SAM :: build();

    for(int T = 1; T <= m; T++) {
        int l = gi(), r = gi();
        q[lp[r]].pb(pi(l, T));
    }
    pre_dfs(1);
    work(1);
    for(int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
    return 0; 
}