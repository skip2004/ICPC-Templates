struct plane { 
	vec3 n; db d; // n dot x = d
	plane() {}
	plane(vec3 a, vec3 b, vec3 c) : n((c - a) * (b - a)) {
		d = n % a;
	}
	db side(vec3 x) const { return n % x - d; }
	db dist(vec3 w) const { return side(w) / n.abs(); }
	vec3 proj(vec3 w) const { return w - n * (side(w) / n.abs()); }
};
