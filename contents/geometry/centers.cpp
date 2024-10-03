p2 bary(p2 a, p2 b, p2 c, db A, db B, db C) {
	return (a * A + b * B + c * C) / (A + B + C);
}
p2 centroid(p2 A, p2 B, p2 C) {
    return bary(A, B, C, 1, 1, 1);
} // 重心
p2 circumcenter(p2 A, p2 B, p2 C) {
    db a = (B - C).norm(), b = (C - A).norm(), c = (A - B).norm();
    return bary(A, B, C, a*(b+c-a), b*(c+a-b), c*(a+b-c));
} // 外心，外接圆圆心，三边中垂线的交点
p2 incenter(p2 A, p2 B, p2 C) {
    return bary(A, B, C, (B-C).abs(), (A-C).abs(), (A-B).abs());
} // 内心，内接圆圆心，三角角平分线的交点
p2 orthocenter(p2 A, p2 B, p2 C) {
    db a = (B - C).norm(), b = (C - A).norm(), c = (A - B).norm();
    return bary(A, B, C, (a+b-c)*(c+a-b), (b+c-a)*(a+b-c), (c+a-b)*(b+c-a));
} // 垂心，三条高线所在的交点
p2 excenter(p2 A, p2 B, p2 C) {
    db a = (B - C).abs(), b = (A - C).abs(), c = (A - B).abs();
    return bary(A, B, C, -a, b, c);
    // return bary(A, B, C, a, -b, c);
    // return bary(A, B, C, a, b, -c);
} // 旁心 一个内角的平分线和其他两个内角的外角平分线的交点
