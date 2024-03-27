vector<int>G[sz];
namespace bipolar_orientation {
	int dfn[sz],low[sz],cc,p[sz],inv[sz],topo[sz];
	bool flg,sgn[sz];
	void dfs(int x,int fa,int s,int t) {
		dfn[x]=low[x]=++cc; inv[cc]=x,p[x]=fa;
		if (x==s) dfs(t,x,s,t);
		for (int y:G[x]) {
			if (x==s&&y==t) continue;
			if (!dfn[y]) {
				dfs(y,x,s,t);
				chkmin(low[x],low[y]);
				if (x==s||low[y]>=dfn[x]) flg=1;
			}
			else if (dfn[y]<dfn[x]&&y!=fa) chkmin(low[x],dfn[y]);
		}
	}
	int check(int s,int t,int n) { // return topo
		if (n==1) return topo[1]=1,1;
		if (s==t) return 0;
		cc=flg=0; dfs(s,s,s,t);
		if (flg) return 0;
		sgn[s]=0;
		static int pre[sz],suf[sz];
		suf[0]=s,pre[s]=0,suf[s]=t;
		pre[t]=s,suf[t]=n+1,pre[n+1]=t;
		rep(i,3,n) {
			int v=inv[i];
			if (!sgn[inv[low[v]]]) {
				int P=pre[p[v]];
				pre[v]=P,suf[v]=p[v];
				suf[P]=pre[p[v]]=v;
			}
			else {
				int S=suf[p[v]];
				pre[v]=p[v],suf[v]=S;
				suf[p[v]]=pre[S]=v;
			}
			sgn[p[v]]=!sgn[inv[low[v]]];
		}
		for (int x=s,cnt=0;x!=n+1;x=suf[x]) topo[++cnt]=x;
		return 1;
	}
	void clr(int n) {
		rep(i,1,n) dfn[i]=low[i]=p[i]=inv[i]=topo[i]=sgn[i]=0,G[i].clear();
	}
}
