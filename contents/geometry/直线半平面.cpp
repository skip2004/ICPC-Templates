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
