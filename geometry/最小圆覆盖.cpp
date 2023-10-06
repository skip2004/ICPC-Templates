struct circle : vec2 { db r; };
circle incircle(vec2 a, vec2 b, vec2 c) {
	db A = (b - c).abs(), B = (c - a).abs(), C = (a - b).abs();
	return {(a * A + b * B + c * C) / (A + B + C), fabs((b - a) * (c - a)) / (A + B + C)};
} // 三点确定内心，不是最小圆覆盖内容
circle circumcenter(vec2 a, vec2 b, vec2 c) { 
	vec2 bc = c - b, ca = a - c, ab = b - a;
	vec2 o = (b + c - r90(bc) * (ca % ab) / (ca * ab)) / 2;
	return {o, (a - o).abs()};
}// 三点确定外心
circle cir(vec2 a, vec2 b) { // 根据直径生成圆
	return {(a + b) / 2, (a - b).abs() / 2};
}
bool in(circle x, vec2 y) { return (vec2(x) - y).abs() <= x.r + eps; }
circle mincircle(std::vector<vec2> a) { // 最小圆覆盖，需要 shuffle
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
				o = circumcenter(a[i], a[j], a[k]);
			}
		}
	}
	return o;
}
