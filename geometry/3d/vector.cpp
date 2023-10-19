struct vec3 {
	db x, y, z;
	db norm() const { return x * x + y * y + z * z; }
	db abs() const { return std::sqrt(norm()); }
};
vec3 operator + (vec3 x, vec3 y) { return {x.x + y.x, x.y + y.y, x.z + y.z}; }
vec3 operator - (vec3 x, vec3 y) { return {x.x - y.x, x.y - y.y, x.z - y.z}; }
vec3 operator * (vec3 x, db y) { return {x.x * y, x.y * y, x.z * y}; }
vec3 operator / (vec3 x, db y) { return {x.x / y, x.y / y, x.z / y}; }
vec3 operator * (vec3 x, vec3 y) { // 三维叉积需要更高的精度
	return {
		x.y * y.z - x.z * y.y,
		x.z * y.x - x.x * y.z,
		x.x * y.y - x.y * y.x
	};
}
db operator % (vec3 x, vec3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }
vec3 perpvec(vec3 x) {
	return fabs(x.x) > fabs(x.z) ? vec3{ x.y, -x.x, 0 } : vec3{0, -x.z, x.y};
} // 找到一个与给定向量垂直的向量
db area(vec3 a, vec3 b, vec3 c) { return ((b - a) * (c - a)).abs(); } // 三角形面积两倍
db volume(vec3 d, vec3 a, vec3 b, vec3 c) { // 四面体有向体积六倍
	return (d - a) % ((b - a) * (c - a));
}
