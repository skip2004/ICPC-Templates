// 完全没有测试
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = long double;
const db eps = 1e-6;

struct p3 {
	db x, y, z;
	db norm() const { return x * x + y * y + z * z; }
	db abs() const { return std::sqrt(norm()); }
};
p3 operator + (p3 x, p3 y) { return {x.x + y.x, x.y + y.y, x.z + y.z}; }
p3 operator - (p3 x, p3 y) { return {x.x - y.x, x.y - y.y, x.z - y.z}; }
p3 operator * (p3 x, db y) { return {x.x * y, x.y * y, x.z * y}; }
p3 operator / (p3 x, db y) { return {x.x / y, x.y / y, x.z / y}; }
p3 operator * (p3 x, p3 y) { // 三维叉积需要更高的精度
	return {
		x.y * y.z - x.z * y.y,
		x.z * y.x - x.x * y.z,
		x.x * y.y - x.y * y.x
	};
}
db operator % (p3 x, p3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }
p3 perpvec(p3 x) {
	return fabs(x.x) > fabs(x.z) ? p3{ x.y, -x.x, 0 } : p3{0, -x.z, x.y};
} // 找到一个与给定向量垂直的向量
db area(p3 a, p3 b, p3 c) { return ((b - a) * (c - a)).abs(); } // 三角形面积两倍
db volume(p3 d, p3 a, p3 b, p3 c) { // 四面体有向体积六倍
	return (d - a) % ((b - a) * (c - a));
}

struct plane { 
	p3 n; db d; // n dot x = d
	plane() {}
	plane(p3 a, p3 b, p3 c) : n((c - a) * (b - a)) {
		d = n % a;
	}
	db side(p3 x) const { return n % x - d; }
	db dist(p3 w) const { return side(w) / n.abs(); }
	p3 proj(p3 w) const { return w - n * (side(w) / n.abs()); }
};

// need testing -----------------------------------
struct line3 {
	p3 d, o; // kd + o
	line3() {}
	line3(p3 p, p3 q) : d(q - p), o(p) {}
	line3(plane p1, plane p2) : d(p1.n * p2.n) { // 平面交出直线
		o = (p2.n * p1.d - p1.n * p2.d) * d / d.norm();
	}
	db dist(p3 p) const { return (d * (p - o)).abs() / d.abs(); }
	p3 proj(p3 p) const { return o + d * (d % (p - o)) / d.norm(); } // 投影
	p3 relf(p3 p) const { return proj(p) * 2 - p; } // 对称
	p3 operator & (const plane & p) const { // 线与平面交
		return o - d * p.side(o) / (p.n % d);
	}
};
db dist(line3 l1, line3 l2) {
	p3 n = l1.d * l2.d;
	if(n.abs() < eps) return l1.dist(l2.o);
	return abs((l2.o - l1.o) % n) / n.abs();
}
p3 closestOnL1(line3 l1, line3 l2) {
	p3 n2 = l2.d * (l1.d * l2.d);
	return l1.o + l1.d * ((l2.o - l1.o) % n2) / (l1.d % n2);
}
bool ispara(plane p1, plane p2) { return (p1.n * p2.n).abs() < eps; } // 判断是否相交
bool isperp(plane p1, plane p2) { return fabs(p1.n % p2.n) < eps; } // 判断是否垂直
bool ispara(line3 p1, line3 p2) { return (p1.d * p2.d).abs() < eps; } // 判断是否相交
bool isperp(line3 p1, line3 p2) { return fabs(p1.d % p2.d) < eps; } // 判断是否垂直
line3 perpthrough(plane p, p3 o) { return line3(o, o + p.n); } // 过平面一点做垂线
// need testing -----------------------------------

const int N = 2005;
struct face { int a[3]; plane p; };
int vis[N][N];
std::vector<face> f;
void convex3d(const std::vector<p3> & a) { // need to deal coplane 
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
int main() {
#ifdef zqj
	freopen("$.in", "r", stdin);
#endif
	std::ios::sync_with_stdio(false), cin.tie(0);
	int T; cin >> T;
	for(int i = 0;i < T;++i) {
		int n;
		cin >> n;
		std::vector<p3> a(n);
		for(auto & [x, y, z] : a) {
			cin >> x >> y >> z;
		}
		convex3d(a);
		p3 zr{};
		db ar = 0, v = 0;
		for(auto x : f) {
			ar += area(a[x.a[0]], a[x.a[1]], a[x.a[2]]);
			v += volume(zr, a[x.a[0]], a[x.a[1]], a[x.a[2]]);
		}
		printf("%.5Lf %.5Lf\n", ar / 2, v / 6);
	}
}
