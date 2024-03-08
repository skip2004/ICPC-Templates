#include<bits/stdc++.h>
using std::cin, std::cout;

using ll = long long;
using i128 = __int128;
using Q = struct Quad*;
using db = double;

struct p2 {
	int x, y;
	ll norm() const { return (ll) x * x + (ll) y * y; }
	db dist() const { return sqrt(norm()); }
};
p2 operator + (p2 x, p2 y) { return {x.x + y.x, x.y + y.y}; }
p2 operator - (p2 x, p2 y) { return {x.x - y.x, x.y - y.y}; }
ll operator * (p2 x, p2 y) { return (ll) x.x * y.y - (ll) x.y * y.x; }
bool operator == (const p2 & x, const p2 & y) {
	return x.x == y.x && x.y == y.y;
}
bool operator < (const p2 & x, const p2 & y) {
	if(x.x != y.x) return x.x < y.x;
	return x.y < y.y;
}

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
}

template<class A, class F>
void dela(A& v, F f) {
	auto ret = triangulate(v);
	int N = size(ret);
	assert(N % 3 == 0);
	std::map<p2, int> lut;
	for(int i = 0;i < (int) v.size();++i)
		lut[v[i]] = i;
	for (int a = 0; a < (int) size(ret); a += 3) {
		f(lut[ret[a]], lut[ret[a+1]], lut[ret[a+2]]);
	}
}

int main() {
	std::mt19937 gen;
	for(int i = 0;i < 500000;++i) {
		{
			// if (it % 200 == 0) cerr << endl;
			std::vector<p2> ps;
			int N = gen() % 50 + 1;
			int xrange = gen() % 100 + 1;
			int yrange = gen() % 100 + 1;
			for(int i = 0;i < N;++i) {
				ps.emplace_back(gen() % (2*xrange) - xrange, gen() % (2*yrange) - yrange);
			}

			for(int i = 0;i < N;++i)
				for(int j = 0;j < i;++j) {
					if (ps[i] == ps[j]) {  goto fail; }
				}

			bool allColinear = true;
			if (N >= 3) {
				for(int i = 2;i < N;++i)
					if ((ps[i] - ps[0]) * (ps[1] - ps[0])) allColinear = false;
			}

			auto fail = [&]() {
				cout << "Points:" << std::endl;
				for(auto &p: ps) {
					cout << p.x << ' ' << p.y << std::endl;
				}

				cout << "Triangles:" << std::endl;
				dela(ps, [&](int i, int j, int k) {
					cout << i << ' ' << j << ' ' << k << std::endl;
				});

				abort();
			};

			ll sumar = 0;
			std::vector<int> used(N);
			bool any = false;
			dela(ps, [&](int i, int j, int k) {
				any = true;
				used[i] = used[j] = used[k] = 1;
				ll ar = cross(ps[i], ps[j], ps[k]);
				if (ar <= 0) {
					fail();
				}
				sumar += ar;
				for(int l = 0;l < N;++l) {
					if(circ(ps[l], ps[i], ps[j], ps[k])) {
						fail();
					}
				}
			});
			if (!allColinear) {
				for(int i = 0;i < N;++i)
					if (!used[i]) {
						fail();
					}
			} else {
				assert(!any);
			}
			auto convexHull = [&](std::vector<p2> o) { 
				sort(o.begin(), o.end(), [](p2 x, p2 y) { return x.x == y.x ? x.y < y.y : x.x < y.x; });
				std::vector<p2> stack;
				for(int i = 0;i < (int) o.size();++i) {
					for(;stack.size() >= 2 && cross(stack.rbegin()[1], stack.back(), o[i]) <= 0;) {
						stack.pop_back();
					}
					stack.push_back(o[i]);
				}
				for(int i = o.size() - 2, t = stack.size();i >= 0;--i) {
					for(;(int) stack.size() > t && cross(stack.rbegin()[1], stack.back(), o[i]) <= 0;) {
						stack.pop_back();
					}
					stack.push_back(o[i]);
				}
				stack.pop_back();
				return stack;
			};

			std::vector<p2> hull = convexHull(ps);
			ll ar2 = 0;
			for(int i = 2;i < (int) hull.size();++i) {
				ar2 += cross(hull[0], hull[i - 1], hull[i]);
			}
			if (ar2 != sumar) {
				fail();
			}

			if(i % 1000 == 0) {
				std::cerr << "done " << i << '\n';
			}
			continue;
		}
fail:--i;
	}
	cout<<"Tests passed!"<<std::endl;
	// cerr << endl;
	return 0;
}
