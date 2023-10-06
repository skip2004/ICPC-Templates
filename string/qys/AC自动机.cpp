const int sig = 26;
int son[N][sig], fail[N], cnt;
int ins(const char * c) {
    int x = 0;
    for(;*c;++c) {
        int & p = son[x][*c - 'a'];
        if(!p) p = ++ cnt;
        x = p;
    }
    return x;
}
void build_ac() {
    std::queue<int> Q;
    for(int i = 0;i < sig;++i) if(son[0][i]) Q.push(son[0][i]);
    for(;Q.size();) {
        int x = Q.front(); Q.pop();
        for(int i = 0;i < sig;++i)
            if(son[x][i]) fail[son[x][i]] = son[fail[x]][i], Q.push(son[x][i]);
            else son[x][i] = son[fail[x]][i];
    }
}
