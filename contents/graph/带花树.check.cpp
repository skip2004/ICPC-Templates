// https://uoj.ac/submission/684863
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

#define sz 555

namespace blossom {
	vector<int>V[sz];
	int f[sz];
	int n,match[sz];
	int getfa(int x){return f[x]==x?x:f[x]=getfa(f[x]);}
	void link(int x,int y){V[x].push_back(y),V[y].push_back(x);}
	int pre[sz],mk[sz];
	int vis[sz],T;
	queue<int>q;
	int LCA(int x,int y) {
		T++;
		for (;;x=pre[match[x]],swap(x,y))
			if (vis[x=getfa(x)]==T) return x;
			else vis[x]=x?T:0;
	}
	void flower(int x,int y,int z) {
		while (getfa(x)!=z) {
			pre[x]=y; y=match[x]; f[x]=f[y]=z; x=pre[y];
			if (mk[y]==2) q.push(y),mk[y]=1;
		}
	}
	void aug(int s){
		for (int i=1;i<=n;i++) pre[i]=mk[i]=vis[i]=0,f[i]=i;
		q={};
		mk[s]=1; q.push(s);
		while (q.size()) {
			int x=q.front(); q.pop();
			for (auto v:V[x]) {
				int y=v,z;
				if (mk[y]==2) continue;
				if (mk[y]==1) z=LCA(x,y),flower(x,y,z),flower(y,x,z);
				else if (!match[y]) {
					for (pre[y]=x;y;) x=pre[y],match[y]=x,swap(y,match[x]);
					return;
				}
				else pre[y]=x,mk[y]=2,q.push(match[y]),mk[match[y]]=1;
			}
		}
	}
	int work() {
		rep(i,1,n) if (!match[i]) aug(i);
		int res=0;
		rep(i,1,n) res+=match[i]>i;
		return res;
	}
}

int main() {
	file();
	int n,m,x,y; cin>>n>>m;
	blossom::n=n;
	while (m--) cin>>x>>y,blossom::link(x,y);
	cout<<blossom::work()<<'\n';
	rep(i,1,n) cout<<blossom::match[i]<<" \n"[i==n];
	return 0;
}