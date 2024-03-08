using db = long double;
const db eps = 1e-10;
db sgn(db x) { return x < -eps ? -1 : x > eps; }
db eq(db x, db y) { return !sgn(x - y); }
struct p2 {
	db x, y;
	db norm() const { return x * x + y * y; }
	db abs() const { return std::sqrt(x * x + y * y); }
	db arg() const { return atan2(y, x); }
};
db arg(p2 x, p2 y) {
	db a = y.arg() - x.arg();
	if(a > pi) a -= pi * 2;
	if(a < -pi) a += pi * 2;
	return a;
}
p2 r90(p2 x) { return {-x.y, x.x}; }
p2 operator + (p2 x, p2 y) { return {x.x + y.x, x.y + y.y}; }
p2 operator - (p2 x, p2 y) { return {x.x - y.x, x.y - y.y}; }
p2 operator / (p2 x, db y) { return {x.x / y, x.y / y}; }
p2 operator * (p2 x, db y) { return {x.x * y, x.y * y}; }
p2 operator * (db y, p2 x) { return {x.x * y, x.y * y}; }
db operator * (p2 x, p2 y) { return x.x * y.y - x.y * y.x; }
db operator % (p2 x, p2 y) { return x.x * y.x + x.y * y.y; }
int half(p2 x){return x.y < 0 || (x.y == 0 && x.x <= 0); }
int half(p2 x){return x.y < -eps || (std::fabs(x.y) < eps && x.x < eps);}
bool cmp(p2 a, p2 b) { return half(a) == half(b) ? a * b > 0 : half(b); }
bool cmp_eq(p2 A, p2 B) { return half(A) == half(B) && eq(A * B, 0) ; }
// 判断 A, B, C 三个向量是否是逆时针顺序
// 如果是，返回 1
// 如果 (A, B), (C, B) 同方向共线，返回 -1
// 如果是顺时针，返回 0
bool cmp_ct(p2 A, p2 B, p2 C) {
	if(cmp_eq(A, B)) return -1;
	if(cmp_eq(C, B)) return -1;
	if(cmp(A, B)) {
		return cmp(B, C) || cmp(C, A);
	} else {
		return cmp(B, C) && cmp(C, A);
	}
}
// 凸包 DP
struct pr { int i, j; p2 get() const { return a[j] - a[i]; } };
bool cmpseg(pr x, pr y) {
	p2 A = x.get(), B = y.get();
	if(!cmp(A, B) && !cmp(B, A)) return a[x.i] % A < a[y.i] % A;
	return cmp(A, B);
}
