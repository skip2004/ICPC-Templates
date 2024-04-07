#include<bits/stdc++.h>
using std::cin, std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = long double;
const db eps = 1e-10;
const db pi = std::acos(-1);
db sgn(db x) { return x < -eps ? -1 : x > eps; }
db eq(db x, db y) { return !sgn(x - y); }
struct p2 {
	db x, y;
	db norm() const { return x * x + y * y; }
	db abs() const { return std::sqrt(x * x + y * y); }
	db arg() const { return atan2(y, x); }
};
db arg(p2 x, p2 y) {
	db a = y.arg() - x.arg();
	if(a > pi) a -= pi * 2;
	if(a < -pi) a += pi * 2;
	return a;
}
p2 r90(p2 x) { return {-x.y, x.x}; }
p2 operator + (p2 x, p2 y) { return {x.x + y.x, x.y + y.y}; }
p2 operator - (p2 x, p2 y) { return {x.x - y.x, x.y - y.y}; }
p2 operator / (p2 x, db y) { return {x.x / y, x.y / y}; }
p2 operator * (p2 x, db y) { return {x.x * y, x.y * y}; }
p2 operator * (db y, p2 x) { return {x.x * y, x.y * y}; }
db operator * (p2 x, p2 y) { return x.x * y.y - x.y * y.x; }
db operator % (p2 x, p2 y) { return x.x * y.x + x.y * y.y; }
int half(p2 x){return x.y < -eps || (std::fabs(x.y) < eps && x.x < eps);}
bool cmp(p2 a, p2 b) { return half(a) == half(b) ? a * b > 0 : half(b); }
bool cmp_eq(p2 A, p2 B) { return half(A) == half(B) && eq(A * B, 0) ; }
// 判断 A, B, C 三个向量是否是逆时针顺序
// 如果是，返回 1
// 如果 (A, B), (C, B) 同方向共线，返回 -1
// 如果是顺时针，返回 0
bool cmp_ct(p2 A, p2 B, p2 C) {
	if(cmp_eq(A, B)) return -1;
	if(cmp_eq(C, B)) return -1;
	if(cmp(A, B)) {
		return cmp(B, C) || cmp(C, A);
	} else {
		return cmp(B, C) && cmp(C, A);
	}
}
// 凸包 DP
struct line : p2 {
	db z;
	// a * x + b * y + c (= or >) 0
	line() = default;
	line(db a, db b, db c) : p2{a, b}, z(c) {}
	line(p2 a, p2 b) : p2(r90(b - a)), z(a * b) { } //左侧 > 0
	db operator ()(p2 a) const { return a % p2(*this) + z; }
	line perp() const { return {y, -x, 0}; } // 垂直
	line para(p2 o) { return {x, y, z - (*this)(o)}; } // 平行
};
p2 operator & (line x, line y) {
	return p2{p2{x.z, x.y} * p2{y.z, y.y}, p2{x.x, x.z} * p2{y.x, y.z}} / -(p2(x) * p2(y));
	// 注意此处精度误差较大，以及 res.y 需要较高精度
}
p2 proj(p2 x, line l){return x - p2(l) * (l(x) / l.norm());}//投影
p2 refl(p2 x, line l){return x - p2(l) * (l(x) / l.norm()) * 2;}//对称
db dist(line l, p2 x={0, 0}){return l(x) / l.abs();}//有向点到线距离
bool is_para(line x, line y){return eq(p2(x) * p2(y), 0);}//判断线平行
bool is_perp(line x, line y){return eq(p2(x) % p2(y), 0);}//判断线垂直
bool online(p2 x, line l) { return eq(l(x), 0); } // 判断点在线上
int ccw(p2 a, p2 b, p2 c) {
	int sign = sgn((b - a) * (c - a));
	if(sign == 0) {
		if(sgn((b - a) % (c - a)) == -1) return 2;
		if((c - a).norm() > (b - a).norm() + eps) return -2;
	}
	return sign;
}
db det(line a, line b, line c) {
	p2 A = a, B = b, C = c;
	return c.z * (A * B) + a.z * (B * C) + b.z * (C * A);
}
db check(line a, line b, line c) { // sgn same as c(a & b), 0 if error
	return sgn(det(a, b, c)) * sgn(p2(a) * p2(b));
}
bool paraS(line a, line b) { // 射线同向
	return is_para(a, b) && p2(a) % p2(b) > 0;
}
struct seg {
	p2 x, y;
	seg() {}
	seg(const p2 & A, const p2 & B) : x(A), y(B) {}
	bool onseg(const p2 & o) const {
		return (o - x) % (o - y) < eps && std::fabs((o - x) * (o - y)) < eps;
	}
};
db dist(const seg & o, const p2 & x) {
	if((o.x - o.y) % (x - o.y) <= eps) return (x - o.y).abs();
	if((o.y - o.x) % (x - o.x) <= eps) return (x - o.x).abs();
	return fabs((o.x - x) * (o.y - x) / (o.x - o.y).abs());
}
bool is_isc(const seg & x, const seg & y) {
	return
		ccw(x.x, x.y, y.x) * ccw(x.x, x.y, y.y) <= 0 &&
		ccw(y.x, y.y, x.x) * ccw(y.x, y.y, x.y) <= 0;
}
db dist(const seg & x, const seg & y) {
	if(is_isc(x, y)) return 0;
	return std::min({dist(y, x.x), dist(y, x.y), dist(x, y.x), dist(x, y.y)});
}

using polygon = std::vector<p2>;
// counter-clockwise  
db area(const polygon & x) {
	db res = 0;
	for(int i = 2;i < (int) x.size();++i) {
		res += (x[i - 1] - x[0]) * (x[i] - x[0]);
	}
	return res / 2;
}
bool is_convex(const polygon & x, bool strict = 1) {
	// warning, maybe wrong
	const db z = strict ? eps : -eps;
	for(int i = 2;i < (int) x.size() + 2;++i) {
		if((x[(i - 1) % x.size()] - x[i - 2]) * (x[i % x.size()] - x[i - 2]) < z) return 0;
	}
	return 1;
}
int contain(const std::vector<p2> & a, p2 o) { // 简单多边形包含判定
	bool in = 0;
	for(int i = 0;i < (int) a.size();++i) {
		p2 x = a[i] - o, y = a[(i + 1) % a.size()] - o;
		if(x.y > y.y) std::swap(x, y);
		if(x.y <= eps && y.y > eps && x * y < -eps) in ^= 1;
		if(std::fabs(x * y) < eps && x % y < eps) return 1; // 在线段上，看情况改
	}
	return in * 2;
}
std::vector<p2> cut(const std::vector<p2> & o, line l) {
	std::vector<p2> res;
	int n = size(o);
	for(int i = 0;i < n;++i) {
		p2 a = o[i], b = o[(i + 1) % n];
		if(sgn(l(a)) >= 0) res.push_back(a); // 注意 sgn 精度
		if(sgn(l(a)) * sgn(l(b)) < 0) res.push_back(line(a, b) & l);
	}
	if(res.size() <= 2) return {};
	return res;
} // 切凸包


int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	std::vector<p2> v(n);
	for(auto & [x, y] : v) {
		cin >> x >> y;
	}
	int q;
	cin >> q;
	for(int i = 0;i < q;++i) {
		p2 x; cin >> x.x >> x.y;
		p2 y; cin >> y.x >> y.y;
		line l(x, y);
		auto res = cut(v, l);
		printf("%.10Lf\n", area(res));
	}
}
