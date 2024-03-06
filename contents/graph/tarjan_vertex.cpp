int dfn[sz],low[sz],cc;
stack<int>S;
int T;
void dfs(int x,int fa) {
	dfn[x]=low[x]=++cc; S.push(x);
	for (auto v:V[x]) if (v!=fa) {
		if (!dfn[v]) dfs(v,x),chkmin(low[x],low[v]);
		else chkmin(low[x],dfn[v]);
	}
	if (fa&&low[x]>=dfn[fa]) {
		int y; ++T;
		do y=S.top(),S.pop(),V2[T].push_back(y),V2[y].push_back(T); while (y!=x);
		V2[T].push_back(fa),V2[fa].push_back(T);
	}
}
