struct line3 {
	vec3 d, o; // kd + o
	line3() {}
	line3(vec3 p, vec3 q) : d(q - p), o(p) {}
	line3(plane p1, plane p2) : d(p1.n * p2.n) { // 平面交出直线
		o = (p2.n * p1.d - p1.n * p2.d) * d / d.norm();
	}
	db dist(vec3 p) const { return (d * (p - o)).abs() / d.abs(); }
	vec3 proj(vec3 p) const { return o + d * (d % (p - o)) / d.norm(); }//投影
	vec3 relf(vec3 p) const { return proj(p) * 2 - p; } // 对称
	vec3 operator & (const plane & p) const { // 线与平面交
		return o - d * p.side(o) / (p.n % d);
	}
};
db dist(line3 l1, line3 l2) {
	vec3 n = l1.d * l2.d;
	if(n.abs() < eps) return l1.dist(l2.o);
	return abs((l2.o - l1.o) % n) / n.abs();
}
vec3 closestOnL1(line3 l1, line3 l2) {
	vec3 n2 = l2.d * (l1.d * l2.d);
	return l1.o + l1.d * ((l2.o - l1.o) % n2) / (l1.d % n2);
}
bool ispara(plane p1, plane p2){return(p1.n * p2.n).abs() < eps;}//判断是否相交
bool ispara(line3 p1, line3 p2){return(p1.d * p2.d).abs() < eps;}//判断是否相交
bool isperp(plane p1, plane p2){return fabs(p1.n % p2.n) < eps;}//判断是否垂直
bool isperp(line3 p1, line3 p2){return fabs(p1.d % p2.d) < eps;}//判断是否垂直
line3 perpthrough(plane p, vec3 o){return line3(o, o + p.n);}//过平面一点做垂线
