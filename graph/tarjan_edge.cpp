int dfn[sz],low[sz],cc;
stack<int>S;
int bel[sz],T;
void dfs(int x,int fa) { // cannot handle multiple edges
	dfn[x]=low[x]=++cc; S.push(x);
	for (auto v:V[x]) if (v!=fa) {
		if (!dfn[v]) dfs(v,x),chkmin(low[x],low[v]);
		else chkmin(low[x],dfn[v]);
	}
	if (dfn[x]==low[x]) {
		int y; ++T;
		do y=S.top(),S.pop(),bel[y]=T; while (y!=x);
	}
}
