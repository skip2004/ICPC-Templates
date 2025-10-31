// https://www.luogu.com.cn/problem/P3376
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

#define N 5555

int n;
// S 编号最小，T 最大，或者改一下清空
struct Dinic {
	struct T {
		int to, nxt; ll v;
	} e[N << 3];
	int h[N], head[N], num = 1;
	void link(int x, int y, ll v) {
		e[++num] = {y, h[x], v}, h[x] = num;
		e[++num] = {x, h[y], 0}, h[y] = num; // !!!
	}
	int dis[N];
	bool bfs(int s, int t) {
		std::queue<int> Q;
		for(int i = 1;i <= n;++i) dis[i] = -1, head[i] = h[i]; //如果编号不是[S,T]，只要改这里
		for(Q.push(t), dis[t] = 0;!Q.empty();) {
			int x = Q.front(); Q.pop();
			for(int i = h[x];i;i = e[i].nxt) if(e[i ^ 1].v && dis[e[i].to] < 0) {
				dis[e[i].to] = dis[x] + 1, Q.push(e[i].to);
			}
		}
		return dis[s] >= 0;
	}
	ll dfs(int s, int t, ll lim) {
		if(s == t || !lim) return lim;
		ll ans = 0, mn;
		for(int & i = head[s];i;i = e[i].nxt) {
			if(dis[e[i].to] + 1 == dis[s] && (mn = dfs(e[i].to, t, std::min(lim, e[i].v)))) {
				e[i].v -= mn, e[i ^ 1].v += mn;
				ans += mn, lim -= mn;
				if(!lim) break;
			}
		}
		return ans;
	}
	ll flow(int s, int t) {
		ll ans = 0;
		for(;bfs(s, t);) ans += dfs(s, t, 1e18);
		return ans;
	}
} G;

int main() {
	file();
	int m,s,t; cin>>n>>m>>s>>t;
	int x,y,z;
	rep(i,1,m) cin>>x>>y>>z,G.link(x,y,z);
	cout<<G.flow(s,t)<<'\n';
	return 0;
}