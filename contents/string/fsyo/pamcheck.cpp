//https://www.luogu.com.cn/record/154728217
#include <bits/stdc++.h>
using namespace std;
#define cs const
#define pb push_back

cs int N = 5e5 + 5; 
char S[N];
int n; 
namespace pam {
	int ch[N][26], len[N], lk[N], rp, las, nd, top[N], d[N], dep[N];
	void init() { rp = 0, las = nd = 1, len[1] = -1, lk[0] = 1; }
	// remember to set S[0] = * 
	int jmp(int x) { while(S[rp - len[x] - 1] != S[rp]) x = lk[x]; return x; }
	void ins(int c) {
		++ rp; int p = jmp(las);
		if(!ch[p][c]) {
			int x = ++ nd; 
			len[x] = len[p] + 2; 
			lk[x] = ch[jmp(lk[p])][c];
            dep[x] = dep[lk[x]] + 1; 
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
    scanf("%s", S + 1);
    S[0] = '*';
    n = strlen(S + 1);
    int k = 0; 
    pam :: init();
    for(int i = 1; i <= n; i++) {
        int c = S[i] - 'a';
        c = (c + k) % 26;
        S[i] = c + 'a';
        // cout << S[i] << endl;
        pam :: ins(c);
        k = pam :: dep[pam :: las];
        cout << k << ' ';
    }
    cout << '\n';
}