struct plane { 
	p3 n; db d; // n dot x = d
	plane() {}
	plane(p3 a, p3 b, p3 c) : n((c - a) * (b - a)) { d = n % a; }
	db side(p3 x) const { return n % x - d; }
	db dist(p3 w) const { return side(w) / n.abs(); }
	p3 proj(p3 w) const { return w - n * (side(w) / n.abs()); }
};
