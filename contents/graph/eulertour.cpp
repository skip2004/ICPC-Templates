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
