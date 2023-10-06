// 完全没有测试
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using ll = long long;
using u64 = unsigned long long;
using db = long double;
const db eps = 1e-10;

struct vec3 {
	db x, y, z;
	db norm() const { return x * x + y * y + z * z; }
	db abs() const { return std::sqrt(norm()); }
};
vec3 operator + (vec3 x, vec3 y) { return {x.x + y.x, x.y + y.y, x.z + y.z}; }
vec3 operator - (vec3 x, vec3 y) { return {x.x - y.x, x.y - y.y, x.z - y.z}; }
vec3 operator * (vec3 x, db y) { return {x.x * y, x.y * y, x.z * y}; }
vec3 operator * (vec3 x, vec3 y) { // 三维叉积需要更高的精度
	return {
		x.y * y.z - x.z * y.y,
		x.z * y.x - x.x * y.z,
		x.x * y.y - x.y * y.x
	};
}
db operator % (vec3 x, vec3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }
db area(vec3 a, vec3 b, vec3 c) { // 三角形面积
	return ((b - a) * (c - a)).abs();
}
db volume(vec3 a, vec3 b, vec3 c, vec3 d) { // 四面体有向体积六倍
	return (d - a) % ((b - a) * (c - a));
}

struct plane : vec3 { 
	db w; // w 需要更高的精度
	plane() {}
	plane(vec3 a, vec3 b, vec3 c) : vec3((c - a) * (b - a)) {
		w = -(vec3(*this) % a);
	}
	db test(vec3 x) const { return vec3{*this} % x + w; }
};

db dist(const plane & o, vec3 w) { // 点到平面有向距离
	return o.test(w) / vec3{o}.abs();
}
vec3 proj(const plane & o, vec3 w) { // 点在平面上的投影
	return w - vec3{o} * (o.test(w) / vec3{o}.abs());
}

struct line3 {
	vec3 k, a;
	line3() {}
	line3(vec3 x, vec3 y) : k(x - y), a(x) { }
};
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
}
