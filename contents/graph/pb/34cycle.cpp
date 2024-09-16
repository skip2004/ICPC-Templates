static int id[sz],rnk[sz];
rep(i,1,n) id[i]=i;
sort(id+1,id+n+1,[](int x,int y){return pii{deg[x],x}<pii{deg[y],y};});
rep(i,1,n) rnk[id[i]]=i;
rep(i,1,n) for (auto v:V[i]) if (rnk[v]>rnk[i]) V2[i].push_back(v);
int ans3=0; // 3-cycle
rep(i,1,n) {
	static int vis[sz];
	for (auto v:V2[i]) vis[v]=1;
	for (auto v1:V2[i]) for (auto v2:V2[v1]) if (vis[v2]) ++ans3; // (i,v1,v2)
	for (auto v:V2[i]) vis[v]=0;
}
ll ans4=0; // 4-cycle
rep(i,1,n) {
	static int vis[sz];
	for (auto v1:V[i]) for (auto v2:V2[v1]) if (rnk[v2]>rnk[i]) ans4+=vis[v2],vis[v2]++;
	for (auto v1:V[i]) for (auto v2:V2[v1]) vis[v2]=0;
}
