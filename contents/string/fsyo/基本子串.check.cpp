// https://codeforces.com/contest/1817/submission/255430160
#include <bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
using pi = pair <int, int>; 
using ll = long long; 
cs int N = 2e5 + 5;

int n; 
char S[N];

struct SAM {
int ch[N][26], lk[N], len[N];
int las, nd, r[N], ed[N];
vector <int> e[N];
int A[N];
int tag[N];
int sz[N];
int fa[N][20];
void defau() {
    las = nd = 1; 
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
}
void dfs(int u) {
    fa[u][0] = lk[u];
    sz[u] = 1; 
    for(int i = 1; i <= 18; i++)    
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int v : e[u])
        dfs(v), sz[u] += sz[v];
}
void init() {
    static int bin[N];
    memset(bin, 0, sizeof (int) * (n + 1));
    for(int i = 1; i <= nd; i++) ++ bin[len[i]];
    for(int i = 1; i <= n; i++) bin[i] += bin[i - 1];
    for(int i = nd; i; i--) A[bin[len[i]]--] = i; 
    for(int i = 1; i <= nd; i++) e[lk[i]].pb(i);
    dfs(1);
}
int fnd(int x, int le) {
    for(int i = 18; ~i; i--)
    if(len[fa[x][i]] >= le) x = fa[x][i];
    return x; 
}
} T[2];

int cnt, rt[2][N];
vector <int> vec[2][N];
vector <pi> pnt[N];
ll ans[N];
using pii = pair <pair <int, int>, int >; 
vector <pii> qry[N];

namespace bit {
int c[N], tim, ex[N];
void add(int x, int w) {
    ++ x; 
    for(; x; x -= x & -x) {
        if(ex[x] != tim) ex[x] = tim, c[x] = 0; 
        c[x] += w; 
    }
}
int ask(int x) {
    ++ x; 
    int w = 0; 
    for(; x <= n; x += x & -x) {
        if(ex[x] != tim) ex[x] = tim, c[x] = 0;
        w += c[x];
    }
    return w; 
}
};

int main() {
    #ifdef zqj
    freopen("1.in","r",stdin);
    #endif
    scanf("%s", S + 1);
    n = strlen(S + 1);
    T[0].defau();
    T[1].defau();
    for(int i = 1; i <= n; i++) 
        T[0].extend(S[i] - 'a', i); 
    for(int i = n; i; i--)  
        T[1].extend(S[i] - 'a', i);
    T[0].init();
    T[1].init();

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
    } // vec[0] : from left to right, node id of the colunm , vec[1] : from down to up

    ll ans = 0;
    for(int t = 1; t <= cnt; t++) {
        vector <ll> sl, sr; 
        int rt = :: rt[0][t];

        int U = T[0].r[rt] - T[0].len[rt] + 1; 
        int R = T[0].r[rt];
        int L = R - vec[0][t].size() + 1; 
        int D = U + vec[1][t].size() - 1;

        // cout << L << ' ' << R << ' ' << U << ' ' << D << endl;

        for(int x : vec[1][t]) {
            int num = T[1].len[x] - T[1].len[T[1].lk[x]];
            sr.pb(num);
        }
        for(int i = 1; i < sr.size(); i++) sr[i] += sr[i - 1];
        // 0 -> D, 1 -> D - 1
        for(int x : vec[0][t]) {
            int num = T[0].len[x] - T[0].len[T[0].lk[x]];
            if(D - L - 1 >= 0)
                ans += 1ll * num * sr[D - L - 1], assert(D - L - 1 < sr.size());
            ++ L; 
        }
    }
    cout << ans << '\n';
    return 0; 
}