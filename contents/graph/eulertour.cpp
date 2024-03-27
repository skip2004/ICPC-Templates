vector<pii>V[sz];
vector<int>ans; // reverse ans in the end
void dfs(int x) {
    static int vis[sz];
    while (V[x].size()) {
        auto [to,id]=V[x].back();
        V[x].pop_back();
        if (!vis[id]) vis[id]=1,dfs(to),ans.push_back(id);
    }
}