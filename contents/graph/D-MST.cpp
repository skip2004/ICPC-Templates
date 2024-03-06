namespace DMST {
	struct edge {
		int u, v, id; ll w;
		bool operator < (const edge & y) const {
			return w < y.w;
		}
	} ent[N], val[M];
	int ls[M], rs[M], size[M], cc; ll tag[M];
	int fs[N], fw[N], rt[N];
	void put(int x, ll v) {
		if(x) val[x].w += v, tag[x] += v;
	}
	void pushdown(int x) {
		put(ls[x], tag[x]);
		put(rs[x], tag[x]);
		tag[x] = 0;
	}
	int merge(int x, int y) {
		if(!x || !y) return x | y;
		if(val[y] < val[x]) std::swap(x, y);
		pushdown(x), rs[x] = merge(rs[x], y);
		if(size[rs[x]] > size[ls[x]]) {
			std::swap(ls[x], rs[x]);
		}
		size[x] += size[y];
		return x;
	}
	void ins(int & x, const edge & z) {
		val[++cc] = z, size[cc] = 1;
		x = merge(x, cc);
	}
	void pop(int & x) { x = merge(ls[x], rs[x]); }
	edge top(int x) { return val[x]; }
	int find(int x, int * anc) {
		return anc[x] == x ? x : anc[x] = find(anc[x], anc);
	}
	void link(int u, int v, int w, int id) {
		ins(rt[v], {u, v, id, w});
	}
	int pa[N * 2], tval[N * 2], up[N * 2], end_edge[M], cmt, baned[M];
	std::vector<int> solve(int r) {
		std::queue<int> roots;
		for(int i = 1;i <= n;++i) {
			fs[i] = fw[i] = i, tval[i] = ++ cmt;
			if(i != r) roots.push(i);
		}
		std::vector<edge> H;
		std::vector<int> ret;
		for(;!roots.empty();) {
			int k = roots.front(); roots.pop();
			if(!rt[k]) return ret;
			edge e = top(rt[k]); pop(rt[k]);
			int i = e.u, j = e.v;
			if(find(i, fs) == k) roots.push(k);
			else {
				H.push_back(e); end_edge[e.id] = tval[k];
				if(find(i, fw) != find(j, fw)) {
					fw[find(j, fw)] = i;
					ent[k] = e;
				} else {
					pa[tval[k]] = ++ cmt, up[tval[k]] = e.id;
					put(rt[k], -e.w);
					for(;(e = ent[find(e.u, fs)]).u;) {
						int p = find(e.v, fs);
						pa[tval[p]] = cmt;
						up[tval[p]] = e.id;
						put(rt[p], -e.w);
						rt[k] = merge(rt[k], rt[p]);
						fs[p] = k;
					}
					tval[k] = cmt;
					roots.push(k);
				}
			}
		}
		reverse(H.begin(), H.end());
		for(edge i : H) if(!baned[i.id]) {
			ret.push_back(i.id);
			for(int j = i.v;j != end_edge[i.id];j = pa[j]) ++ baned[up[j]];
		}
		sort(ret.begin(), ret.end());
		return ret;
	}
}
