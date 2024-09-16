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