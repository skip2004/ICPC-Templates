int c[N][26], fail[N], len[N], tot;
void init() {
    fail[0] = 1, len[++tot] = -1;
    // root is 1
}
int get_fail(int o, char * x) {
    for(;*x != x[-len[o] - 1];)
        o = fail[o];
    return o;
}
int append(int o, char * x) {
    o = get_fail(o, x);
    int & p = c[o][*x - 'a'];
    if(!p) {
        fail[++tot] = c[get_fail(fail[o], x)][*x - 'a'];
        len[p = tot] = len[o] + 2;
    }
    return p;
}
BorderPam
info atom[N];
int c[N][26], fail[N], len[N], tot;
int diff[N], bigfail[N];
/*---------------------------------------*/
// 严格 logn 插入，但是很可能不要
void init() {
    bigfail[0] = fail[0] = 1, len[++tot] = -1;
    // root is 1
}
int get_fail(int o, char * x) {
    for(;*x != x[-len[o] - 1];) {
        o = (*x != x[-len[fail[o]] - 1] ? bigfail : fail)[o];
    }
    return o;
}
/*----------------------------*/
void init() {
    fail[0] = 1, len[++tot] = -1;
    // root is 1
}
int get_fail(int o, char * x) {
    for(;*x != x[-len[o] - 1];)
        o = fail[o];
    return o;
}
int append(int o, char * x) {
    o = get_fail(o, x);
    int & p = c[o][*x - 'a'];
    if(!p) {
        fail[++tot] = c[get_fail(fail[o], x)][*x - 'a'];
        len[p = tot] = len[o] + 2;
        diff[p] = len[p] - len[fail[p]];
        bigfail[p] = diff[p] == diff[fail[p]] ? bigfail[fail[p]] : fail[p];
    }
    return p;
}
info node[N];
info query(int x, int i) {
    info z = {};
    for(;x;x = bigfail[x]) {
        const int go = bigfail[x], fa = fail[x];
        info & t = node[x] = atom[i - len[go] - diff[x]];
        if(fa != go) t = node[fa] + t;
        z = t + z;
    }
    return z;
}
