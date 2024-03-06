int fa[sz];
int getfa(int x){return x==fa[x]?x:fa[x]=getfa(fa[x]);}
int pre[sz],match[sz],tp[sz];
queue<int>q;
int vis[sz],T;
int lca(int x,int y) { for (++T;;swap(x,y)) if (x) { x=getfa(x); if (vis[x]==T) return x; vis[x]=T,x=pre[match[x]]; } }
void shrink(int x,int y,int l) {
	while (getfa(x)!=l) {
		pre[x]=y,y=match[x];
		if (tp[y]==2) tp[y]=1,q.push(y);
		if (x==fa[x]) fa[x]=l;
		if (y==fa[y]) fa[y]=l;
		x=pre[y]; 
	}
}
int work(int s) {
	while (q.size()) q.pop(); q.push(s);
	rep(i,1,n) fa[i]=i,pre[i]=0,tp[i]=0;
	tp[s]=1;
	while (!q.empty()) {
		int x=q.front();q.pop();
		rep(v,1,n) if (e[x][v]) {
			if (getfa(x)==getfa(v)||tp[v]==2) continue;
			if (!tp[v]) {
				pre[v]=x;
				if (!match[v]) {
					for (int cur=v;cur;swap(cur,match[pre[cur]])) match[cur]=pre[cur];
					return match[0]=0,1;
				}
				tp[v]=2,tp[match[v]]=1,q.push(match[v]);
			}
			else { int l=lca(x,v); shrink(x,v,l),shrink(v,x,l); }
		}
	}
}
