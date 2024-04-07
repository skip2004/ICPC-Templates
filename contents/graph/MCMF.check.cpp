// https://qoj.ac/contest/1536/problem/2021
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

#define sz 5555

int n;
// S 编号最小，T 最大，或者改一下清空
namespace mcmf {
	int L,R;
	using pr = std::pair<ll, int>;
	const int N = 10005, M = 1e6 + 10;
	struct edge {
		int to, nxt, v, f;
	} e[M << 1];
	int h[N], num = 1;
	void link(int x, int y, int v, int f) {
		e[++num] = {y, h[x], v, f}, h[x] = num;
		e[++num] = {x, h[y], 0, -f}, h[y] = num;
	}
	void rev(int x,int y) {
		int hy=e[num].nxt; --num;
		h[y]=hy;
		int hx=e[num].nxt; --num;
		h[x]=hx;
	}
	ll d[N], dis[N];
	int vis[N], fr[N];
	bool spfa(int s, int t) {
		std::queue<int> Q;
		std::fill(d + 1, d + n + 10, 1e18);
		for(d[s] = 0, Q.push(s);!Q.empty();) {
			int x = Q.front(); Q.pop(); vis[x] = 0;
			for(int i = h[x];i;i = e[i].nxt)
				if(e[i].v && d[e[i].to] > d[x] + e[i].f) {
					d[e[i].to] = d[x] + e[i].f;
					fr[e[i].to] = i;
					if(!vis[e[i].to]) vis[e[i].to] = 1, Q.push(e[i].to);
				}
		}
		return d[t] < 1e17;
	}
	bool dijkstra(int s, int t) { // 正常题目不需要 dijk
		std::priority_queue<pr, std::vector<pr>, std::greater<pr>> Q;
		for(int i = 1;i <= n+10;++i) dis[i] = d[i], d[i] = 1e18, vis[i] = fr[i] = 0;
		for(Q.emplace(d[s] = 0, s);!Q.empty();) {
			int x = Q.top().second; Q.pop();
			if(vis[x]) continue;
			vis[x] = 1;
			for(int i = h[x];i;i = e[i].nxt) {
				const ll v = e[i].f + dis[x] - dis[e[i].to];
				if(e[i].v && d[e[i].to] > d[x] + v) {
					fr[e[i].to] = i;
					Q.emplace(d[e[i].to] = d[x] + v, e[i].to);
				}
			}
		}
		for(int i = 1;i <= n+10;++i) d[i] += dis[i];
		return d[t] < 1e17;
	}
	std::pair<ll, ll> EK(int s, int t) {
		spfa(s, t); // 如果初始有负权且要 dijk
		ll f = 0, c = 0;
		for(;dijkstra(s, t);) { // 正常可以用 spfa
			ll fl = 1e18;
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) fl = std::min<ll>(e[i].v, fl);
			for(int i = fr[t];i;i = fr[e[i ^ 1].to]) e[i].v -= fl, e[i ^ 1].v += fl;
			f += fl, c += fl * d[t];
		}
		return std::make_pair(f, c);
	}
}

int main() {
	file();
	ios::sync_with_stdio(false),cin.tie(0);
	int m,s,t; cin>>n>>m>>s>>t;
	int a,b,l,u,c;
	ll tot=0;
	static int deg[sz];
	int ss=n+1,tt=n+2;
	rep(i,1,m) {
		cin>>a>>b>>l>>u>>c;
		if (c>=0) mcmf::link(a,b,u-l,c),tot+=1ll*l*c,deg[a]+=l,deg[b]-=l;
		else tot+=1ll*u*c,mcmf::link(b,a,u-l,-c),deg[a]+=u,deg[b]-=u;
	}
	rep(i,1,n) if (deg[i]>0) mcmf::link(i,tt,deg[i],0); else mcmf::link(ss,i,-deg[i],0);
	mcmf::link(t,s,1e9,0);
	auto [flow, cost]=mcmf::EK(ss,tt);
	rep(i,1,n) flow-=max(deg[i],0);
	if (flow) return cout<<"-1\n",0;
	tot+=cost;
	int ff=mcmf::e[mcmf::num].v;
	mcmf::rev(t,s);
	drep(i,n,1) if (deg[i]>0) mcmf::rev(i,tt); else mcmf::rev(ss,i);
	auto [_flow, _cost]=mcmf::EK(s,t);
	cout<<ff+_flow<<' '<<tot+_cost<<'\n';
	return 0;
}