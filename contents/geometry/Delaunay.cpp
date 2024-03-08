using i128 = __int128;
using Q = struct Quad*;
p2 arb(LLONG_MAX, LLONG_MAX);
struct Quad {
	Q rot, o; p2 p = arb; bool mark;
	p2& F() { return r() -> p; }
	Q& r() { return rot->rot; }
	Q prev() { return rot->o->rot; }
	Q next() { return r()->prev(); }
} *H;
ll cross(p2 a, p2 b, p2 c) {
	return (b - a) * (c - a);
}
bool circ(p2 p, p2 a, p2 b, p2 c) { // p 是否在 a, b, c 外接圆中
	i128 p2 = p.norm(), A = a.norm() - p2, B = b.norm() - p2, C = c.norm() - p2;
	a = a - p, b = b - p, c = c - p;
	return (a * b) * C + (b * c) * A + (c * a) * B > 0;
}
Q link(p2 orig, p2 dest) {
	Q r = H ? H : new Quad{new Quad{new Quad{new Quad{0}}}};
	H = r -> o; r -> r() -> r() = r;
	for(int i = 0;i < 4;++i)
		r = r -> rot, r -> p = arb, r -> o = i & 1 ? r : r -> r();
	r -> p = orig, r -> F() = dest;
	return r;
}
void splice(Q a, Q b) {
	std::swap(a -> o -> rot -> o, b -> o -> rot -> o);
	std::swap(a -> o, b -> o);
}
Q conn(Q a, Q b) {
	Q q = link(a -> F(), b -> p);
	splice(q, a -> next());
	splice(q -> r(), b);
	return q;
}
std::pair<Q, Q> rec(const std::vector<p2> & s) {
	int N = size(s);
	if(N <= 3) {
		Q a = link(s[0], s[1]), b = link(s[1], s.back());
		if(N == 2) return {a, a -> r()};
		splice(a -> r(), b);
		ll side = cross(s[0], s[1], s[2]);
		Q c = side ? conn(b, a) : 0;
		return {side < 0 ? c->r() : a, side < 0 ? c : b -> r() };
	}
#define H(e) e -> F(), e -> p
#define valid(e) (cross(e->F(), H(base)) > 0)
	int half = N / 2;
	auto [ra, A] = rec({s.begin(), s.end() - half});
	auto [B, rb] = rec({s.end() - half, s.end()});
	while((cross(B -> p, H(A)) < 0 && (A = A -> next())) ||
			(cross(A -> p, H(B)) > 0 && (B = B -> r() -> o)));
	Q base = conn(B -> r(), A);
	if(A -> p == ra -> p) ra = base -> r();
	if(B -> p == rb -> p) rb = base;
#define DEL(e, init, dir) Q e = init -> dir; if(valid(e)) \
	for(;circ(e -> dir -> F(), H(base), e -> F());) { \
		Q t = e -> dir; \
		splice(e, e -> prev()); \
		splice(e -> r(), e -> r() -> prev()); \
		e -> o = H, H = e, e = t; \
	}
	for(;;) {
		DEL(LC, base -> r(), o);
		DEL(RC, base, prev());
		if(!valid(LC) && !valid(RC)) break;
		if(!valid(LC) || (valid(RC) && circ(H(RC), H(LC)))) 
			base = conn(RC, base -> r());
		else
			base = conn(base -> r(), LC -> r());
	}
	return {ra, rb};
}
std::vector<p2> triangulate(std::vector<p2> a) {
	sort(a.begin(), a.end()); // unique
	if((int)size(a) < 2) return {};
	Q e = rec(a).first;
	std::vector<Q> q = {e};
	while(cross(e -> o -> F(), e -> F(), e -> p) < 0) e = e -> o;
#define ADD { Q c = e; do { c -> mark = 1; a.push_back(c -> p); \
	q.push_back(c -> r()), c = c -> next(); } while(c != e); }
	ADD; a.clear();
	for(int qi = 0;qi < (int) size(q);) if(!(e = q[qi++]) -> mark) ADD;
	return a;
} // 返回若干逆时针三角形 \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\}
