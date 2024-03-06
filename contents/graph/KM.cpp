int n,m;
ll e[sz][sz];
ll lw[sz],rw[sz];
int lpr[sz],rpr[sz];
int vis[sz],fa[sz];
ll mnw[sz];
void work(int x) {
	int xx=x;
	rep(i,1,n) vis[i]=0,mnw[i]=1e18;
	while (233) {
		rep(i,1,n) if (!vis[i]&&chkmin(mnw[i],lw[x]+rw[i]-e[x][i])) fa[i]=x; 
		ll mn=1e18; int y=-1;
		rep(i,1,n) if (!vis[i]&&chkmin(mn,mnw[i])) y=i;
		lw[xx]-=mn; rep(i,1,n) if (vis[i]) rw[i]+=mn,lw[rpr[i]]-=mn; else mnw[i]-=mn;
		if (rpr[y]) x=rpr[y],vis[y]=1; else { while (y) rpr[y]=fa[y],swap(y,lpr[fa[y]]); return; }
	}
}
int main() {
	read(n,m);
	rep(i,1,n) rep(j,1,n) e[i][j]=lw[i]=-1e18;
	int x,y,z;
	while (m--) read(x,y,z),e[x][y]=z,chkmax(lw[x],1ll*z);
	rep(i,1,n) work(i);
	ll ans=0; rep(i,1,n) ans+=e[i][lpr[i]];
	printf("%lld\n",ans);
	rep(i,1,n) printf("%d ",rpr[i]);
}
