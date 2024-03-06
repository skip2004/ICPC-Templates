struct seg {
	vec2 x, y;
	seg() {}
	seg(const vec2 & A, const vec2 & B) : x(A), y(B) {}
	bool onseg(const vec2 & o) const {
		return (o - x) % (o - y) < eps && std::fabs((o - x) * (o - y)) < eps;
	}
};
db dist(const seg & o, const vec2 & x) {
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
