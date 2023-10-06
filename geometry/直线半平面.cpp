struct line : vec2 {
	db z;
	// a * x + b * y + c (= or >) 0
	line() = default;
	line(db a, db b, db c) : vec2{a, b}, z(c) {}
	line(vec2 a, vec2 b) : vec2(r90(b - a)), z(a * b) { }
	// 左侧 > 0
	db operator ()(vec2 a) const { return a % vec2(*this) + z; }
	line perp() const { return {y, -x, 0}; } // 垂直
	line para(vec2 o) { return {x, y, z - (*this)(o)}; } // 平行
};
vec2 operator & (line x, line y) {
	return vec2{vec2{x.z, x.y} * vec2{y.z, y.y}, vec2{x.x, x.z} * vec2{y.x, y.z}} / -(vec2(x) * vec2(y));
	// 注意此处精度误差较大，以及 res.y 需要较高精度
}
vec2 proj(vec2 x, line l) { return x - vec2(l) * (l(x) / l.norm()); } // 投影
vec2 refl(vec2 x, line l) { return x - vec2(l) * (l(x) / l.norm()) * 2; } // 对称
db dist(line l, vec2 x = vec2{0, 0}) { return l(x) / l.abs(); } // 有向点到线距离
bool is_para(line x, line y) { return eq(vec2(x) * vec2(y), 0); } // 判断线平行
bool is_perp(line x, line y) { return eq(vec2(x) % vec2(y), 0); } // 判断线垂直
bool online(vec2 x, line l) { return eq(l(x), 0); } // 判断点在线上
int ccw(vec2 a, vec2 b, vec2 c) {
	int sign = sgn((b - a) * (c - a));
	if(sign == 0) {
		if(sgn((b - a) % (c - a)) == -1) return 2;
		if((c - a).norm() > (b - a).norm() + eps) return -2;
	}
	return sign;
}
// 三条直线关系
db det(line a, line b, line c) {
	vec2 A = a, B = b, C = c;
	return c.z * (A * B) + a.z * (B * C) + b.z * (C * A);
}
db check(line a, line b, line c) { // sgn same as c(a & b), 0 if error
	return sgn(det(a, b, c)) * sgn(vec2(a) * vec2(b));
}
bool paraS(line a, line b) { // 射线同向
	return is_para(a, b) && vec2(a) % vec2(b) > 0;
}

