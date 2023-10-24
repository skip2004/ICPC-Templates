struct circle : vec2 { db r; };
std::vector<vec2> operator & (circle o, line l) {
	vec2 v = l, Rv = r90(v); db L = l.abs();
	db d = l(vec2(o)) / L, x = o.r * o.r - d * d;
	if(x < -eps) return {};
	x = std::sqrt(x * sgn(x));
	vec2 z = vec2(o) - d / L * v, p = Rv * (x / L);
	return {z + p, z - p};
} // l 如果是构造函数给出，那么返回交点按射线顺序
std::vector<vec2> operator & (circle o, seg s) {
	std::vector<vec2> b;
	for(vec2 x : (o & s.to_l()))
		if(s.onseg(x)) b.push_back(x);
	return b;
}
std::vector<vec2> operator & (circle o0, circle o1) {
	vec2 tmp = 2 * (vec2(o1) - vec2(o0));
	return o0 & line(tmp.x, tmp.y, o1.r * o1.r - o0.r * o0.r + o0.norm() - o1.norm());
}
std::vector<vec2> tang(circle o, vec2 x) {
	db d = (x - vec2(o)).abs();
	if(d <= o.r + eps) return {};
	return o & circle{x, sqrt(d * d - o.r * o.r)};
}
// 三角形 (0, a, b) 和圆 o 的交的有向面积 * 2
db intersect(circle o, vec2 a, vec2 b) {
	a = a - vec2(o), b = b - vec2(o); o.x = o.y = 0;
	int va = a.abs() <= o.r + eps;
	int vb = b.abs() <= o.r + eps;
	if(va && vb) return a * b;
	auto v = o & seg{a, b}; // 注意这里，有必要改一下 onseg，去掉平行判定
	if(v.empty()) return arg(a, b) * o.r * o.r;
	db sum = 0;
	sum += va ? a * v[0] : arg(a, v[0]) * o.r * o.r;
	sum += vb ? v.back() * b : arg(v.back(), b) * o.r * o.r;
	if(v.size() > 1) sum += v[0] * v[1];
	return sum;
}
// 有向弓形面积 * 2, arg 不能改
db csegS(circle o, vec2 a, vec2 b) {
	a = a - vec2(o);
	b = b - vec2(o);
	db d = b.arg() - a.arg();
	if(d < 0) d += pi * 2;
	return d * o.r * o.r - a * b;
}
// 两圆交的面积 * 2
db intersect(circle o0, circle o1) {
	if(o0.r > o1.r) std::swap(o0, o1);
	db d = (vec2(o0) - vec2(o1)).abs();
	if(d <= (o1.r - o0.r) + eps) return 2 * pi * o0.r * o0.r;
	if(d >= o1.r + o0.r - eps) return 0;
	auto v = o0 & o1;
	return csegS(o0, v[1], v[0]) + csegS(o1, v[0], v[1]);
}
