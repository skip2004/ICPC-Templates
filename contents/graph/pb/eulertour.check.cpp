// https://uoj.ac/submission/684823
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

#define sz 202020

namespace Euler {
    bool directed;
    vector<pii>V[sz];
    vector<int>ans; // reverse ans in the end
    int vis[sz];
    int dfs(int x) {
        vector<int>t;
        while (V[x].size()) {
            auto [to,id]=V[x].back();
            V[x].pop_back();
            if (!vis[abs(id)]) vis[abs(id)]=1,t.push_back(dfs(to)),ans.push_back(id);
        }
        rep(i,1,(int)t.size()-1) if (t[i]!=x) ans.clear();
        return t.size()?t[0]:x;
    }
    int n,m;
    pii e[sz];
    int deg[sz],vv[sz];
    void clr() {
        rep(i,1,n) V[i].clear(),deg[i]=vv[i]=0;
        rep(i,1,m) vis[i]=0;
        ans.clear();
        n=m=0;
    }
    void addedge(int x,int y) {
        chkmax(n,x),chkmax(n,y); ++m;
        e[m]={x,y};
        if (directed) {
            V[x].push_back({y,m});
            ++deg[x],--deg[y],vv[x]=vv[y]=1;
        }
        else {
            V[x].push_back({y,m});
            V[y].push_back({x,-m});
            ++deg[x],++deg[y],vv[x]=vv[y]=1;
        }
    }
    using vi=vector<int>;
    pair<vi,vi> work() {
        if (!m) return clr(),pair<vi,vi>{{1},{}};
        int S=1;
        rep(i,1,n) if (vv[i]) S=i;
        rep(i,1,n) if (deg[i]>0&&deg[i]%2==1) S=i;
        dfs(S);
        if ((int)ans.size()!=m) return clr(),pair<vi,vi>();
        reverse(ans.begin(),ans.end());
        vi ver,edge=ans;
        if (directed) {
            ver={e[ans[0]].fir};
            for (auto t:ans) ver.push_back(e[t].sec);
        }
        else {
            ver={ans[0]>0?e[ans[0]].fir:e[-ans[0]].sec};
            for (auto t:ans) ver.push_back(t>0?e[t].sec:e[-t].fir);
        }
        clr();
        return {ver,edge};
    }
}

void work() {
    int n,m; cin>>n>>m;
    int x,y;
    rep(i,1,m) cin>>x>>y,Euler::addedge(x,y);
    auto [ver,edge]=Euler::work();
    if (!ver.size()||ver[0]!=ver.back()) cout<<"NO\n";
    else {
        cout<<"YES\n";
        // for (auto v:ver) cout<<v<<' ';
        // cout<<'\n';
        for (auto e:edge) cout<<e<<' ';
        cout<<'\n';
    }
}

int main() {
    file();
    ios::sync_with_stdio(false),cin.tie(0);
    int type; cin>>type;
    Euler::directed=(type==2);
    work();
    // int T; cin>>T;
    // while (T--) work();
    return 0;
}