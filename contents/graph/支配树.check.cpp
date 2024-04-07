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

#define sz 303030

int n;

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
			ANS[idom[x]].push_back(x);fa[x][0]=idom[x];dep[x]=dep[idom[x]]+1;
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
		for (int v:V[x]) if (!dfn[v])
			BuildTree::V[x].push_back(v), BuildTree::deg[v]++, anc[v] = x, dfs(v);
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
		dfs(1);
		rep(i,1,n) fa[i]=i,mn[i]=1e9,semi[i]=i;
		drep(w,n,2) {
			int x=id[w];int cur=1e9;
			if (w>cnt) continue;
			for (int v:rV[x]) {
				if (!dfn[v]) continue;
				if (dfn[v]<dfn[x]) chkmin(cur,dfn[v]);
				else find(v),chkmin(cur,mn[v]);
			}
			semi[x]=id[cur];mn[x]=cur;fa[x]=anc[x];
			BuildTree::V[semi[x]].push_back(x);BuildTree::deg[x]++;
		}
	}
	void link(int x,int y){V[x].push_back(y),rV[y].push_back(x);}
}

vector<int>V[sz];
int siz[sz];
void dfs(int x) {
	siz[x]=1;
	for (auto v:V[x]) dfs(v),siz[x]+=siz[v];
}

int main() {
	file();
	int m; cin>>n>>m;
	int x,y;
	rep(i,1,m) cin>>x>>y,BuildDAG::link(x,y);
	BuildDAG::work(),BuildTree::work();
	rep(i,1,n) V[i]=BuildTree::ANS[i];
	dfs(1);
	rep(i,1,n) cout<<siz[i]<<" \n"[i==n];
	return 0;
}