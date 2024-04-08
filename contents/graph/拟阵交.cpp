// max size, minimum weight
namespace MatroidIntersection {
    int K;
    ll W[sz]; // weight
    int in[sz]; // ans
    namespace Check { // implementation needed
        // recommend writing checker here
        void init() {}
        // return {-1} if no cycle; return cycle otherwise.
        vector<int> cycleA(int x) {}
        vector<int> cycleB(int x) {}
        // not necessary
        void check() {init();}
    }
    bool work() { // try augment
        using pli=pair<ll,int>;
        static vector<int> V[sz];
        static pli dis[sz];
        static int fr[sz];
        Check::init();
        rep(i,1,K) V[i].clear();
        vector<int>A,B;
        rep(i,1,K) if (!in[i]) {
            auto cyca=Check::cycleA(i);
            if (cyca.size()==1u&&cyca[0]==-1) A.push_back(i);
            else for (auto y:cyca) V[y].push_back(i);
            auto cycb=Check::cycleB(i);
            if (cycb.size()==1u&&cycb[0]==-1) B.push_back(i);
            else for (auto y:cycb) V[i].push_back(y);
        }
        rep(i,1,K) dis[i]={ll(1e18),K+1},fr[i]=0;
        priority_queue<pair<pli,int>, vector<pair<pli,int>>, greater<pair<pli,int>>>q;
        for (auto x:A) dis[x]={W[x],0},q.push({dis[x],x});
        while (!q.empty()) {
            auto [ww,x]=q.top(); q.pop();
            if (dis[x]!=ww) continue;
            for (auto v:V[x]) 
                if (chkmin(dis[v],{dis[x].fir+W[v],dis[x].sec+1})) 
                    q.push({dis[v],v}),fr[v]=x;
        }
        pli mn={ll(1e18),K+1}; int mnp=-1;
        for (auto x:B) if (chkmin(mn,dis[x])) mnp=x;
        if (mnp==-1) return 0;
        for (int x=mnp;x;x=fr[x]) in[x]^=1;
        Check::check();
        return 1;
    }
    void clr() {
        rep(i,1,K) in[i]=0;
    }
}
