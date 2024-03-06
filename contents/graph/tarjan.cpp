int dfn[sz],low[sz],cc;
stack<int>S; int in[sz];
int bel[sz],T;
void dfs(int x) {
	dfn[x]=low[x]=++cc; S.push(x),in[x]=1;
	for (auto v:V[x]) {
		if (!dfn[v]) dfs(v,x),chkmin(low[x],low[v]);
		else if (in[v]) chkmin(low[x],dfn[v]);
	}
	if (dfn[x]==low[x]) {
		int y; ++T;
		do y=S.top(),S.pop(),in[y]=0,bel[y]=T; while (y!=x);
	}
}
