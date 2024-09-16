int n;
std::vector<int> edge[N];
int pre[N], match[N], fa[N], vis[N], t[N];
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void aug(int s) {
	std::queue<int> Q;
	for(int i = 1;i <= n;++i) {
		pre[i] = vis[i] = t[i] = 0, fa[i] = i;
	}
	auto lca = [&](int x, int y) {
		static int tick = 0; ++tick;
		for(;;std::swap(x = pre[match[x]], y)) {
			if(vis[x = find(x)] == tick) return x;
			vis[x] = x ? tick : 0;
		}
	};
	auto blossom = [&](int x, int y, int z) {
		for(;find(x) != z;x = pre[y]) {
			pre[x] = y, y = match[x], fa[x] = fa[y] = z;
			if(t[y] == 2) Q.push(y), t[y] = 1;
		}
	};
	Q.push(s), t[s] = 1;
	for(;Q.size();) {
		int x = Q.front(); Q.pop();
		for(int y : edge[x]) {
			if(t[y] == 2) continue;
			if(t[y] == 1) {
				int z = lca(x, y);
				blossom(x, y, z);
				blossom(y, x, z);
			} else if (int p = match[y]) {
				pre[y] = x, t[y] = 2, t[p] = 1;
				Q.push(p);
			} else {
				int z;
				for(pre[y] = x;y;y = z) {
					x = pre[y], z = match[x];
					match[x] = y, match[y] = x;
				}
				return ;
			}
		}
	}
}
void run() {
	for(int i = 1;i <= n;++i) if(!match[i]) {
		aug(i);
	}
}
