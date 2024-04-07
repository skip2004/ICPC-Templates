namespace KM {
	int nl,nr;
	ll e[sz][sz];
	ll lw[sz],rw[sz];
	int lpr[sz],rpr[sz];
	int vis[sz],fa[sz];
	ll mnw[sz];
	void work(int x) {
		int xx=x;
		rep(i,1,nr) vis[i]=0,mnw[i]=1e18;
		while (233) {
			rep(i,1,nr) if (!vis[i]&&chkmin(mnw[i],lw[x]+rw[i]-e[x][i])) fa[i]=x; 
			ll mn=1e18; int y=-1;
			rep(i,1,nr) if (!vis[i]&&chkmin(mn,mnw[i])) y=i;
			lw[xx]-=mn; rep(i,1,nr) if (vis[i]) rw[i]+=mn,lw[rpr[i]]-=mn; else mnw[i]-=mn;
			if (rpr[y]) x=rpr[y],vis[y]=1; else { while (y) rpr[y]=fa[y],swap(y,lpr[fa[y]]); return; }
		}
	}
	void init(int nl,int nr) {
		assert(nl<=nr);
		KM::nl=nl,KM::nr=nr;
		rep(i,1,nl) lw[i]=-1e18;
		rep(i,1,nl) rep(j,1,nr) e[i][j]=0; // or -1e18
	}
	void clr() {
		rep(i,1,nl) lpr[i]=lw[i]=0;
		rep(i,1,nr) rpr[i]=rw[i]=vis[i]=fa[i]=mnw[i]=0;
		rep(i,1,nl) rep(j,1,nr) e[i][j]=0;
	}
	void addedge(int x,int y,ll w){chkmax(e[x][y],w),chkmax(lw[x],w);}
	ll work() {
		rep(i,1,nl) work(i);
		ll tot=0;
		rep(i,1,nl) tot+=e[i][lpr[i]];
		return tot;
	}
}
