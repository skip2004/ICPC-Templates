//https://loj.ac/s/2042450
#include<bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;

typedef pair<int, int> pi;
#define fi first
#define se second
typedef unsigned long long ull;
cs int N = 2e5 + 50; 

int n, m, ans[N];
char S[N];
vector<pi> q[N];
ull h[N], pw[N];
struct run{
	int l, r, p;
} t[N];
int k; 
vector<int> R[N];
vector<int> c[N]; 
unordered_map<ull, int> pt; 

ull H(int l, int r){ return h[r] - h[l - 1] * pw[r - l + 1]; }
int lcp(int x, int y){
	if(S[x] != S[y]) return 0; 
	int l = 1, r = n - max(x, y) + 1; 
	while(l < r){
		int mid = (l + r + 1) >> 1;
		if(H(x, x + mid - 1) == H(y, y + mid - 1))
			l = mid; 
		else r = mid - 1;
	} return l;
}
int lcs(int x, int y){
	if(S[x] != S[y]) return 0;
	int l = 1, r = min(x, y);
	while(l < r){
		int mid = (l + r + 1) >> 1;
		if(H(x - mid + 1, x) == H(y - mid + 1, y))
			l = mid; 
		else r = mid - 1; 
	} return l;
}
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
        t[++ k] = (run){L, R, p};
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

namespace bit{
	int c[N];
	void add(int x, int v){ for(; x <= n; x += x & -x) c[x] += v; }
	int ask(int x){ int s = 0; for(; x; x -= x & -x) s += c[x]; return s; }
}

int main(){
	#ifdef FSYo
	freopen("1.in", "r", stdin);
	#endif
	scanf("%d%d%s", &n, &m, S + 1);
	pw[0] = 1; 
	for(int i = 1; i <= n; i++)
		pw[i] = pw[i - 1] * 223;
	for(int i = 1; i <= n; i++)
		h[i] = h[i - 1] * 223 + S[i];
	
	Run(0), Run(1);
	
	for(int i = 1; i <= k; i++){
		run x = t[i]; 
		int p = x.p * 2; R[x.r].pb(i);
		for(int j = x.l + p - 1; j <= x.r; j++)
			c[j].pb(i);
	}
	
	for(int i = 1, l, r; i <= m; i++){
		scanf("%d%d", &l, &r);
		q[r].pb(pi(l, i));
	}
	for(int i = 1; i <= n; i++){
		for(int z : c[i]){
			run x = t[z]; int p = x.p * 2; 
			int t = (i - x.l + 1) / p;
			int l = i - t * p + 1;
			ull h = H(l, i);
			int o = pt[h];
			if(o) bit :: add(o, -1);
			pt[h] = 0; 
		}
		int d = bit :: ask(i);
		for(auto y : q[i]){
			int ql = y.fi, o = y.se;
			ans[o] = d - bit :: ask(ql - 1);
			for(int z : c[i]) {
				int p = t[z].p, l = i - max(t[z].l, ql) + 1; 
				int t = l % (p * 2), w = l / (p * 2);
				if(!w) continue; 
				ans[o] += w * p - max(0, p - t - 1);
//				cout << "FFF " << o << " " << w * p - max(0, p - t - 1)<< " " << p << " " << t[i].l << ""endl;
			}
		}
		for(int z : R[i]) {
			run x = t[z]; int p = x.p * 2; 
			for(int j = x.l; j + p - 1 <= x.r; j++){
				int t = (x.r - j + 1) / p, r = j + t * p - 1; 
				if(x.r - r >= x.p) continue;
				ull h = H(j, r);
				bit :: add(pt[h] = j, 1);
			}
		}
	}
	for(int i = 1; i <= m; i++)
		cout << ans[i] << '\n';
	return 0; 
}