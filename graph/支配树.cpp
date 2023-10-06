namespace BuildTree {
	int idom[sz];
	vector<int>V[sz],ANS[sz]; // ANS: final tree
	int deg[sz];
	int fa[sz][25],dep[sz];
	int lca(int x,int y) {
		if (dep[x]<dep[y]) swap(x,y);
		drep(i,20,0)
			if (fa[x][i]&&dep[fa[x][i]]>=dep[y])
				x=fa[x][i];
		if (x==y) return x;
		drep(i,20,0)
			if (fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	void work() {
		queue<int>q;q.push(1);
		while (!q.empty()) {
			int x=q.front();q.pop();
			ANS[idom[x]].PB(x);fa[x][0]=idom[x];dep[x]=dep[idom[x]]+1;
			rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
			for (int v:V[x]) {
				--deg[v];if (!deg[v]) q.push(v);
				if (!idom[v]) idom[v]=x;
				else idom[v]=lca(idom[v],x);
			}
		}
	}
}
namespace BuildDAG {
	vector<int>V[sz],rV[sz];
	int dfn[sz],id[sz],anc[sz],cnt;
	void dfs(int x) {
		id[dfn[x]=++cnt]=x;
		for (int v:V[x]) if (!dfn[v]) BuildTree::V[x].PB(v),BuildTree::deg[v]++,anc[v]=x,dfs(v);
	}
	int fa[sz],mn[sz];
	int find(int x) {
		if (x==fa[x]) return x;
		int tmp=fa[x];fa[x]=find(fa[x]);
		chkmin(mn[x],mn[tmp]);
		return fa[x];
	}
	int semi[sz];
	void work() {
		int x,y;
		while (m--) read(x,y),V[x].PB(y),rV[y].PB(x);
		dfs(1);
		rep(i,1,n) fa[i]=i,mn[i]=1e9,semi[i]=i;
		drep(w,n,2) {
			x=id[w];int cur=1e9;
			if (w>cnt) continue;
			for (int v:rV[x]) {
				if (!dfn[v]) continue;
				if (dfn[v]<dfn[x]) chkmin(cur,dfn[v]);
				else find(v),chkmin(cur,mn[v]);
			}
			semi[x]=id[cur];mn[x]=cur;fa[x]=anc[x];BuildTree::V[semi[x]].PB(x);BuildTree::deg[x]++;
		}
	}
}
