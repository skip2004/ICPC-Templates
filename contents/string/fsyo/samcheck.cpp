// https://www.luogu.com.cn/record/154732547
#include<bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
using ll = long long ; 
cs int N = 2e6 + 5; 
char S[N];
int n; 
namespace sam {
int nd, ch[N][26], len[N], lk[N], las, r[N], ed[N], sz[N];
void init() { nd = las = 1;  }
void extend(int c, int k) {
	int x = ++ nd, p = las; las = x;
	len[x] = len[p] + 1, r[x] = k, ed[k] = x; 
	for(; p && !ch[p][c]; p = lk[p]) ch[p][c] = x;   
	if(!p) return lk[x] = 1, void();
	int q = ch[p][c];
	if(len[q] == len[p] + 1)
		return lk[x] = q, void();
	int cl = ++ nd;
	len[cl] = len[p] + 1; 
	memcpy(ch[cl], ch[q], 104);
	lk[cl]= lk[q], lk[q] = lk[x] = cl;
	for(; p && ch[p][c] == q; p = lk[p]) ch[p][c] = cl;
}
int A[N];
void build() { 
	static int bin[N];
	memset(bin, 0, sizeof (int) * (n + 1));
	for(int i = 1; i <= nd; i++) ++ bin[len[i]];
	for(int i = 1; i <= n; i++) bin[i] += bin[i - 1];
	for(int i = nd; i; i--) A[bin[len[i]]--] = i; 
}
ll calc() {
    ll ans = 0; 
    for(int i = nd; i; i--) {
        int x = A[i];
        sz[x] += r[x] > 0;
        sz[lk[x]] += sz[x]; 
        if(sz[x] > 1)
        ans = max(ans, 1ll * sz[x] * len[x]);
    }
    return ans; 
}
}


int main() {
    #ifdef zqj
    freopen("1.in","r",stdin);
    #endif
	scanf("%s", S + 1); n = strlen(S + 1);  	
    sam :: init();
    for(int i = 1; i <= n; i++) {
        sam :: extend(S[i] - 'a', i);
    }
    sam :: build();
    cout << sam :: calc() << '\n';
    return 0; 
} 