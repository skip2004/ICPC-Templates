#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = long double;
const db eps = 1e-5;
const db pi = std::acos(-1);
std::mt19937 gen;


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

int half(p2 x) { return x.y < 0 || (x.y == 0 && x.x <= 0); }
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

p2 bary(p2 a, p2 b, p2 c, db A, db B, db C) {
	return (a * A + b * B + c * C) / (A + B + C);
}
p2 centroid(p2 A, p2 B, p2 C) {
    return bary(A, B, C, 1, 1, 1);
} // 重心
p2 circumcenter(p2 A, p2 B, p2 C) {
    db a = (B - C).norm(), b = (C - A).norm(), c = (A - B).norm();
    return bary(A, B, C, a*(b+c-a), b*(c+a-b), c*(a+b-c));
} // 外心，外接圆圆心，三边中垂线的交点
p2 incenter(p2 A, p2 B, p2 C) {
    return bary(A, B, C, (B-C).abs(), (A-C).abs(), (A-B).abs());
} // 内心，内接圆圆心，三角角平分线的交点
p2 orthocenter(p2 A, p2 B, p2 C) {
    db a = (B - C).norm(), b = (C - A).norm(), c = (A - B).norm();
    return bary(A, B, C, (a+b-c)*(c+a-b), (b+c-a)*(a+b-c), (c+a-b)*(b+c-a));
} // 垂心，三条高线所在的交点
p2 excenter(p2 A, p2 B, p2 C) {
    db a = (B - C).abs(), b = (A - C).abs(), c = (A - B).abs();
    return bary(A, B, C, -a, b, c);
    // return bary(A, B, C, a, -b, c);
    // return bary(A, B, C, a, b, -c);
} // 旁心 一个内角的平分线和其他两个内角的外角平分线的交点

db cross(p2 x, p2 y, p2 z) {
	return (y.x - x.x) * (z.y - x.y) - (y.y - x.y) * (z.x - x.x);
}

std::vector<p2> gethull(std::vector<p2> o) { 
	sort(o.begin(), o.end(), [](p2 x, p2 y) { return eq(x.x, y.x) ? x.y < y.y : x.x < y.x; });
	std::vector<p2> stack;
	for(int i = 0;i < (int) o.size();++i) {
		for(;stack.size() >= 2 && cross(stack.rbegin()[1], stack.back(), o[i]) <= eps;) {
			stack.pop_back();
		}
		stack.push_back(o[i]);
	}
	for(int i = o.size() - 2, t = stack.size();i >= 0;--i) {
		for(;(int) stack.size() > t && cross(stack.rbegin()[1], stack.back(), o[i]) <= eps;) {
			stack.pop_back();
		}
		stack.push_back(o[i]);
	}
	stack.pop_back();
	return stack;
} // 把两个 eps 改成 -eps 可求出所有在凸包上的点

struct line : p2 {
	db z;
	// a * x + b * y + c (= or >) 0
	line() = default;
	line(db a, db b, db c) : p2{a, b}, z(c) {}
	line(p2 a, p2 b) : p2(r90(b - a)), z(a * b) { }
	// 左侧 > 0
	db operator ()(p2 a) const { return a % p2(*this) + z; }
	line perp() const { return {y, -x, 0}; } // 垂直
	line para(p2 o) { return {x, y, z - (*this)(o)}; } // 平行
};
p2 operator & (line x, line y) {
	return p2{p2{x.z, x.y} * p2{y.z, y.y}, p2{x.x, x.z} * p2{y.x, y.z}} / -(p2(x) * p2(y));
	// 注意此处精度误差较大，以及 res.y 需要较高精度
}
p2 proj(p2 x, line l) { return x - p2(l) * (l(x) / l.norm()); } // 投影
p2 refl(p2 x, line l) { return x - p2(l) * (l(x) / l.norm()) * 2; } // 对称
line bisector(p2 x, p2 y) { return line(y, x).perp().para((x + y) / 2); } // x 在半平面一侧
db dist(line l, p2 x = p2{0, 0}) { return l(x) / l.abs(); } // 有向点到线距离
bool is_para(line x, line y) { return eq(p2(x) * p2(y), 0); } // 判断线平行
bool is_perp(line x, line y) { return eq(p2(x) % p2(y), 0); } // 判断线垂直
bool online(p2 x, line l) { return eq(l(x), 0); } // 判断点在线上
int ccw(p2 a, p2 b, p2 c) {
	int sign = sgn((b - a) * (c - a));
	if(sign == 0) {
		if(sgn((b - a) % (c - a)) == -1) return 2;
		if((c - a).norm() > (b - a).norm() + eps) return -2;
	}
	return sign;
}

// 三条直线关系
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
std::vector<p2> HPI(std::vector<line> vs) {
	auto cmp = [](line a, line b) {
		if(paraS(a, b)) return dist(a) < dist(b);
		return ::cmp(p2(a), p2(b));
	};
	sort(vs.begin(), vs.end(), cmp);
	int ah = 0, at = 0, n = size(vs);
	std::vector<line> deq(n + 1);
	std::vector<p2> ans(n);
	deq[0] = vs[0];
	for(int i = 1;i <= n;++i) {
		line o = i < n ? vs[i] : deq[ah];
		if(paraS(vs[i - 1], o)) {
			continue;
		}
		for(;ah < at && check(deq[at - 1], deq[at], o) < 0;) -- at;
		if(i != n)
			for(;ah < at && check(deq[ah], deq[ah + 1], o) < 0;) ++ ah;
		if(!is_para(o, deq[at])) {
			ans[at] = o & deq[at];
			deq[++at] = o;
		}
	}
	if(at - ah <= 2) return {};
	return {ans.begin() + ah, ans.begin() + at};
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
    return std::min({ dist(y, x.x), dist(y, x.y), dist(x, y.x), dist(x, y.y), });
}
db area(const std::vector<p2> & x) {
	db res = 0;
	for(int i = 2;i < (int) x.size();++i) {
		res += (x[i - 1] - x[0]) * (x[i] - x[0]);
	}
	return res / 2;
}
struct circle : p2 { db r; };
std::vector<p2> operator & (circle o, line l) {
	p2 v = l, Rv = r90(v); db L = l.abs();
	db d = l(p2(o)) / L, x = o.r * o.r - d * d;
	if(x < -eps) return {};
	x = std::sqrt(x * sgn(x));
	p2 z = p2(o) - d / L * v, p = Rv * (x / L);
	return {z + p, z - p};
} // l 如果是构造函数给出，那么返回交点按射线顺序
std::vector<p2> operator & (circle o, seg s) {
	std::vector<p2> b;
	for(p2 x : (o & line(s.x, s.y)))
		if(s.onseg(x)) b.push_back(x);
	return b;
}
std::vector<p2> operator & (circle o0, circle o1) {
	p2 tmp = 2 * (p2(o1) - p2(o0));
	return o0 & line(tmp.x, tmp.y, o1.r * o1.r - o0.r * o0.r + o0.norm() - o1.norm());
}
std::vector<p2> tang(circle o, p2 x) {
	db d = (x - p2(o)).abs();
	if(d <= o.r + eps) return {};
	return o & circle{x, sqrt(d * d - o.r * o.r)};
}
// 三角形 (o, a, b) 和圆 o 的交的有向面积 * 2
db intersect(circle o, p2 a, p2 b) {
	a = a - p2(o), b = b - p2(o); o.x = o.y = 0;
	int va = a.abs() <= o.r + eps;
	int vb = b.abs() <= o.r + eps;
	if(va && vb) return a * b;
	auto v = o & seg{a, b};
	if(v.empty()) return arg(a, b) * o.r * o.r;
	db sum = 0;
	sum += va ? a * v[0] : arg(a, v[0]) * o.r * o.r;
	sum += vb ? v.back() * b : arg(v.back(), b) * o.r * o.r;
	if(v.size() > 1) sum += v[0] * v[1];
	return sum;
}
// 有向弓形面积 * 2, arg 不能改
db csegS(circle o, p2 a, p2 b) {
	a = a - p2(o);
	b = b - p2(o);
	db d = b.arg() - a.arg();
	if(d < 0) d += pi * 2;
	return d * o.r * o.r - a * b;
}
// 两圆交的面积 * 2
db intersect(circle o0, circle o1) {
	if(o0.r > o1.r) std::swap(o0, o1);
	db d = (p2(o0) - p2(o1)).abs();
	if(d <= (o1.r - o0.r) + eps) return 2 * pi * o0.r * o0.r;
	if(d >= o1.r + o0.r - eps) return 0;
	auto v = o0 & o1;
	return csegS(o0, v[1], v[0]) + csegS(o1, v[0], v[1]);
}
// 简单多边形处理
int contain(const std::vector<p2> & a, p2 o) {
	bool in = 0;
	for(int i = 0;i < (int) a.size();++i) {
		p2 x = a[i] - o, y = a[(i + 1) % a.size()] - o;
		if(x.y > y.y) std::swap(x, y);
		if(x.y <= eps && y.y > eps && x * y < -eps) in ^= 1;
		if(std::fabs(x * y) < eps && x % y < eps) return 2; // 在线段上，看情况改
	}
	return in;
}
// misc
db mindist(std::vector<p2> a) {
	db ans = 1e18;
	sort(a.begin(), a.end(), [](p2 x, p2 y) { return x.x < y.x; });
	ans = (a[0] - a[1]).abs();
	auto solve = [&](auto s, int l, int r) {
		if(l + 1 == r) return ;
		int mid = (l + r) >> 1;
		db mx = a[mid].x;
		s(s, l, mid), s(s, mid, r);
		static std::vector<p2> b; b.clear();
		inplace_merge(a.begin() + l, a.begin() + mid, a.begin() + r, [](p2 x, p2 y) { return x.y < y.y; });
		for(int i = l;i < r;++i)
			if(fabs(a[i].x - mx) <= ans) b.push_back(a[i]);
		for(int i = 1;i < (int) b.size();++i) 
			for(int j = i - 1;j >= 0 && b[i].y <= b[j].y + ans;--j) ans = std::min(ans, (b[i] - b[j]).abs());
	};
	solve(solve, 0, a.size());
	return ans;
}
circle incircle(p2 a, p2 b, p2 c) {
	db A = (b - c).abs(), B = (c - a).abs(), C = (a - b).abs();
	return {(a * A + b * B + c * C) / (A + B + C), fabs((b - a) * (c - a)) / (A + B + C)};
} // 三点确定内接圆, 不是最小圆覆盖内容
circle circumcircle(p2 a, p2 b, p2 c) {
	p2 bc = c - b, ca = a - c, ab = b - a;
	p2 o = (b + c - r90(bc) * (ca % ab) / (ca * ab)) / 2;
	return {o, (a - o).abs()};
} // 三点确定外接圆
circle cir(p2 a, p2 b) { // 根据直径生成圆
	return {(a + b) / 2, (a - b).abs() / 2};
}
bool in(circle x, p2 y) { return (p2(x) - y).abs() <= x.r + eps; }
circle mincircle(std::vector<p2> a) { // 最小圆覆盖，需要 shuffle
	circle o = {a[0], 0};
	int n = a.size();
	for(int i = 1;i < n;++i) {
		if(in(o, a[i])) continue;
		o = cir(a[0], a[i]);
		for(int j = 1;j < i;++j) {
			if(in(o, a[j])) continue;
			o = cir(a[j], a[i]);
			for(int k = 0;k < j;++k) {
				if(in(o, a[k])) continue;
				o = circumcircle(a[i], a[j], a[k]);
			}
		}
	}
	return o;
}
db convex_diameter(std::vector<p2> & o) {
	int n = size(o);
	db max = 0;
	for(int i = 0, j = 1 % n;i < j;++i) {
		for(;;j = (j + 1) % n) {
			max = std::max(max, (o[j] - o[i]).abs());
			if((o[i + 1] - o[i]) * (o[(j + 1) % n] - o[j]) <= 0) break;
		}
	}
	return max;
} // 凸包直径，不能有三点共线
std::vector<p2> cut(const std::vector<p2> & o, line l) {
	std::vector<p2> res;
	int n = size(o);
	for(int i = 0;i < n;++i) {
		p2 a = o[i], b = o[(i + 1) % n];
		if(sgn(l(a)) >= 0) res.push_back(a); // 注意 sgn 精度
		if(sgn(l(a)) * sgn(l(b)) < 0) res.push_back(line(a, b) & l);
	}
	return res;
} // 切凸包
std::vector<line> cut(const std::vector<line> & o, line l) {
	std::vector<line> res;
	int n = size(o);
	for(int i = 0;i < n;++i) {
		line a = o[i], b = o[(i + 1) % n], c = o[(i + 2) % n];
		int va = check(a, b, l), vb = check(b, c, l);
		assert(check(a, b, c) != 0);
		if(va > 0 || vb > 0 || (va == 0 && vb == 0)) {
			res.push_back(b);
		}
		if(va >= 0 && vb < 0) {
			res.push_back(l);
		}
	}
	return res;
} // 切凸包
std::vector<std::vector<line>> voronoi(std::vector<p2> p) {
	int n = p.size();
	auto b = p; shuffle(b.begin(), b.end(), gen);
	const db V = 3e4; // 边框大小，重要
	std::vector<std::vector<line>> a(n, {
		{V, 0, V * V}, {0, V, V * V},
		{-V, 0, V * V}, {0, -V, V * V},
	});
	for(int i = 0;i < n;++i) {
		for(p2 x : b) if((x - p[i]).abs() > eps) {
			a[i] = cut(a[i], bisector(p[i], x));
		}
	}
	return a;
}

int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	std::vector<p2> a(3);
	for(int i = 0;i < 3;++i) {
		cin >> a[i].x >> a[i].y;
	}
	auto res = incenter(a[0], a[1], a[2]);
	printf("%.10Lf %.10Lf %.10Lf", res.x, res.y, (db)fabs(dist(line(a[0], a[1]), res)));
}
