vector<int>V2[sz],V[sz]; // V2: cactus edges; V: reconstructed tree edges
int m; // set to n before dfs
void dfs(int x,int f) {
	static int mark[sz],fa[sz],vis[sz],dep[sz];
	fa[x]=f; vis[x]=1;dep[x]=dep[f]+1;
	for (auto v:V2[x]) if (v!=f) {
		if (!vis[v]) dfs(v,x);
		else if (dep[v]<dep[x]) {
			++m;
			V[v].push_back(m);
			for (int y=x;y!=v;y=fa[y]) V[m].push_back(y),mark[y]=1;
		}
	}
	if (!mark[x]) {
		++m;
		V[fa[x]].push_back(m),V[m].push_back(x);
	}
}
