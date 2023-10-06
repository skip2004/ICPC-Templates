using polygon = std::vector<vec2>;
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
int contain(const std::vector<vec2> & a, vec2 o) { // 简单多边形包含判定
	bool in = 0;
	for(int i = 0;i < (int) a.size();++i) {
		vec2 x = a[i] - o, y = a[(i + 1) % a.size()] - o;
		if(x.y > y.y) std::swap(x, y);
		if(x.y <= eps && y.y > eps && x * y < -eps) in ^= 1;
		if(std::fabs(x * y) < eps && x % y < eps) return 2; // 在线段上，看情况改
	}
	return in;
}
