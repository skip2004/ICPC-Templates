// https://codeforces.com/contest/932/submission/255419317
#include <bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
cs int mod = 1e9 + 7;
void Add(int &x, int y) {
    if((x += y) >= mod) x -= mod;
}
cs int N = 1e6 + 5; 

int n; 
char S[N];

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
int main() {
    #ifdef FSYo
    freopen("1.in","r",stdin);
    #endif
    static char T[N];
    scanf("%s", T + 1);
    n = strlen(T + 1);
    int c = 0;
    for(int l = n / 2; l; l--) 
        S[++ c] = T[l], S[++ c] = T[n + 1 - l];
    pam :: init();
    static int f[N], g[N];
    f[0] = 1; 
    for(int i = 1; i <= n; i++) {
        pam :: ins(S[i] - 'a'); 
        int x = pam :: las; 
        while(x) {
            if(pam :: d[x] == pam :: d[pam :: lk[x]]) { 
                // when doing dp, the position i - len[x] ~ 
                // i - (len[top[x]] + d[x]) have been updated (in i - d[x])
                g[x] = f[i - pam :: len[pam :: top[x]]];
                Add(g[x], g[pam :: lk[x]]);
            }
            else {
                // update from i - len[x]
                g[x] = f[i - pam :: len[x]];
            } 
            Add(f[i], g[x]);
            x = pam :: lk[pam :: top[x]];
        }
        if(i & 1) f[i] = 0; 
    }
    cout << f[n]; 
    return 0; 
}