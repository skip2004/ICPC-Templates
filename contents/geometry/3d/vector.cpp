struct p3 {
	db x, y, z;
	db norm() const { return x * x + y * y + z * z; }
	db abs() const { return std::sqrt(norm()); }
};
p3 operator + (p3 x, p3 y){ return {x.x + y.x, x.y + y.y, x.z + y.z}; }
p3 operator - (p3 x, p3 y){ return {x.x - y.x, x.y - y.y, x.z - y.z}; }
p3 operator * (p3 x, db y) { return {x.x * y, x.y * y, x.z * y}; }
p3 operator / (p3 x, db y) { return {x.x / y, x.y / y, x.z / y}; }
p3 operator * (p3 x, p3 y) { // 三维叉积需要更高的精度
	return {
		x.y * y.z - x.z * y.y,
		x.z * y.x - x.x * y.z,
		x.x * y.y - x.y * y.x
	};
}
db operator % (p3 x, p3 y) { return x.x * y.x + x.y * y.y + x.z * y.z; }
p3 perpvec(p3 x) {
	return fabs(x.x) > fabs(x.z) ? p3{ x.y, -x.x, 0 } : p3{0, -x.z, x.y};
} // 找到一个与给定向量垂直的向量
db area(p3 a, p3 b, p3 c) { return ((b - a) * (c - a)).abs(); } // 三角形面积两倍
db volume(p3 d, p3 a, p3 b, p3 c) { // 四面体有向体积六倍
	return (d - a) % ((b - a) * (c - a));
}
