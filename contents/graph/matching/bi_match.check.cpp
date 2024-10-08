// https://uoj.ac/submission/684826
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

// 匈牙利，左到右单向边，$O(M|match|)$
std::vector<int> edge[sz];
bool dfs(int x, std::vector<int> & vis, std::vector<int> & match) {
	for(int y : edge[x]) if(!vis[y]) 
		if(vis[y] = 1, !match[y] || dfs(match[y], vis, match)) 
			return match[y] = x, 1;
	return 0;
}
std::vector<int> match(int nl, int nr) {
	std::vector<int> vis(nr + 1), match(nr + 1), ret(nl + 1);
	for(int i = 1;i <= nl;++i) if(dfs(i, vis, match)) 
		memset(vis.data(), 0, vis.size() << 2);
	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
	return ret[0] = 0, ret;
}
// 最小边覆盖
// std::pair<std::vector<int>, std::vector<int>> minedgecover(int nl, int nr) {
// 	std::vector<int> vis(nr + 1), match(nr + 1), ret(nl + 1);
// 	for(int i = 1;i <= nl;++i) if(dfs(i, vis, match))
// 		memset(vis.data(), 0, vis.size() << 2);
// 	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
// 	ret[0] = 0;
// 	for(int i = 1;i <= nl;++i) if(!ret[i]) dfs(i, vis, match);
// 	std::vector<int> le, ri;
// 	for(int i = 1;i <= nl;++i) if(ret[i] && !vis[ret[i]]) le.push_back(i);
// 	for(int i = 1;i <= nr;++i) if(vis[i]) ri.push_back(i);
// 	return std::make_pair(le, ri);
// }
// // 匈牙利，左到右单向边，bitset，$O(n^2/w |match|)$
// using set_ = std::bitset<sz>;
// set_ edge[sz];
// bool dfs(int x, set_ & unvis, std::vector<int> & match) {
// 	for(set_ z = edge[x];;) {
// 		z &= unvis;
// 		int y = z._Find_first();
// 		if(y == N) return 0;
// 		if(unvis.reset(y), !match[y] || dfs(match[y], unvis, match))
// 			return match[y] = x, 1;
// 	}
// }
// std::vector<int> match(int nl, int nr) {
// 	set_ unvis; unvis.set();
// 	std::vector<int> match(nr + 1), ret(nl + 1);
// 	for(int i = 1;i <= nl;++i) 
// 		if(dfs(i, unvis, match)) 
// 			unvis.set();
// 	for(int i = 1;i <= nr;++i) ret[match[i]] = i;
// 	return ret[0] = 0, ret;
// }
// // HK, 左到右单向边，$O(M \sqrt{|match|})$
// std::vector<int> e[sz];
// std::vector<int> matchl, matchr, a, p; 
// std::vector<int> match(int nl, int nr) {
// 	matchl.assign(nl + 1, 0), matchr.assign(nr + 1, 0);
// 	for(;;) {
// 		a.assign(nl + 1, 0), p.assign(nl + 1, 0);
// 		static std::queue<int> Q;
// 		for(int i = 1;i <= nl;++i) 
// 			if(!matchl[i]) a[i] = p[i] = i, Q.push(i);
// 		int succ = 0;
// 		for(;Q.size();) {
// 			int x = Q.front(); Q.pop();
// 			if(matchl[a[x]]) continue;
// 			for(int y : e[x]) {
// 				if(!matchr[y]) {
// 					for(succ = 1;y;x = p[x])
// 						matchr[y] = x, std::swap(matchl[x], y);
// 					break;
// 				}
// 				if(!p[matchr[y]])
// 					Q.push(y = matchr[y]), p[y] = x, a[y] = a[x];
// 			}
// 		}
// 		if(!succ) break;
// 	}
// 	return matchl;
// } // matchl 是左边每个点匹配的右边点编号
// std::pair<std::vector<int>, std::vector<int>> minedgecover(int nl, int nr) {
// 	match(nl, nr);
// 	std::vector<int> l, r;
// 	for(int i = 1;i <= nl;++i) if(!a[i]) l.push_back(i);
// 	for(int i = 1;i <= nr;++i) if(a[matchr[i]]) r.push_back(i);
// 	return {l, r};
// }

int main() {
	file();
	ios::sync_with_stdio(false),cin.tie(0);
	int nl,nr,m; cin>>nl>>nr>>m;
	int x,y;
	rep(i,1,m) cin>>x>>y,edge[x].push_back(y);
	auto res=match(nl,nr);
	int t=0;
	rep(i,1,nl) t+=(res[i]!=0);
	cout<<t<<'\n';
	rep(i,1,nl) cout<<res[i]<<" \n"[i==nl];
	return 0;
}