// https://codeforces.com/problemsets/acmsguru/problem/99999/206
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define templ template<typename T>
	typedef long long ll;
	typedef double db;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
	templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
	templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
	templ inline void read(T& t) {
		t=0;char f=0,ch=getchar();double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
	void file() {
		#ifdef zqj
		freopen("a.in","r",stdin);
		#endif
	}
	inline void chktime() {
		#ifdef zqj
		cerr<<clock()/1000.0<<'\n';
		#endif
	}
	#ifdef mod
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
	ll inv(ll x){return ksm(x,mod-2);}
	#else
	ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
	#endif
}
using namespace my_std;

#define sz 1144

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

ll ww[sz];
vector<pii>V[sz];

vector<int>path;
int dfs(int x,int fa,int goal) {
	if (x==goal) return 1;
	for (auto [v,id]:V[x]) if (v!=fa&&dfs(v,x,goal)) return path.push_back(id),1;
	return 0;
}

int main() {
	file();
	ios::sync_with_stdio(false),cin.tie(0);
	int n,m;
	cin>>n>>m;
	KM::init(n-1,max(n-1,m-n+1));
	int x,y,z;
	rep(i,1,m) {
		cin>>x>>y>>z; ww[i]=z;
		if (i<n) V[x].push_back({y,i}),V[y].push_back({x,i});
		else {
			dfs(x,0,y);
			for (auto t:path) KM::addedge(t,i-n+1,max(ww[t]-ww[i],0ll));
			path.clear();
		}
	}
	ll _tot=KM::work();
	ll tot=0;
	rep(i,1,n-1) tot+=KM::lw[i];
	rep(i,n,m) tot+=KM::rw[i-n+1];
	assert(tot==_tot);
	rep(i,1,m) cout<<ww[i]+(i<n?-KM::lw[i]:KM::rw[i-n+1])<<'\n';
	return 0;
}