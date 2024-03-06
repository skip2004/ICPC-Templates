const int N = 2005;
struct face { int a[3]; plane p; };
int vis[N][N];
std::vector<face> f;
void convex3d(const std::vector<vec3> & a) { // need to deal coplane 
	if(a.size() < 3) return ;
	auto getface = [&](int i, int j, int k) -> face { return {{i, j, k}, plane(a[i], a[j], a[k])}; };
	f = {getface(0, 1, 2), getface(0, 2, 1)};
	std::vector<face> tmp[2];
	for(int i = 3;i < (int) a.size();++i) {
		for(auto x : f) {
			if(x.p.dist(a[i]) < -eps) {
				tmp -> push_back(x);
			} else {
				tmp[1].push_back(x);
				for(int t : {0, 1, 2}) vis[x.a[t]][x.a[(t + 1) % 3]] = i;
			}
		}
		for(auto x : tmp[1]) {
			for(int t : {0, 1, 2}) {
				if(vis[x.a[t]][x.a[(t + 1) % 3]] == i && vis[x.a[(t + 1) % 3]][x.a[t]] != i)
					tmp[0].push_back(getface(x.a[t], x.a[(t + 1) % 3], i));
			}
		}
		f = tmp[0]; tmp[0].clear(); tmp[1].clear();
	}
	for(int i = 0;i < (int)a.size();++i) memset(vis[i], 0, a.size() << 2);
}
