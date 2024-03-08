db cross(p2 x, p2 y, p2 z) { return (y.x - x.x) * (z.y - x.y) - (y.y - x.y) * (z.x - x.x); }
std::vector<p2> gethull(std::vector<p2> o) { 
	sort(o.begin(), o.end(), [](p2 x, p2 y) { return eq(x.x, y.x) ? x.y < y.y : x.x < y.x; });
	std::vector<p2> stack;
	for(int i = 0;i < (int) o.size();++i) {
		for(;stack.size() >= 2 && cross(stack.rbegin()[1], stack.back(), o[i]) <= eps;) {
			stack.pop_back();
		}
		stack.push_back(o[i]);
	}
	for(int i = o.size() - 2, t = stack.size();i >= 0;--i) {
		for(;stack.size() > t && cross(stack.rbegin()[1], stack.back(), o[i]) <= eps;) {
			stack.pop_back();
		}
		stack.push_back(o[i]);
	}
	stack.pop_back();
	return stack;
} // 把两个 eps 改成 -eps 可求出所有在凸包上的点
int findmax(p2 d, const std::vector<p2> & a) {
	int l = 0, r = a.size() - 1;
	if(a[0] % d > a.back() % d) {
		for(;l + 1 < r;) {
			int mid = (l + r) >> 1;
			if(a[mid] % d > a[l] % d && a[mid] % d > a[mid - 1] % d) {
				l = mid;
			} else {
				r = mid;
			}
		}
		return l;
	} else {
		for(;l + 1 < r;) {
			int mid = (l + r) >> 1;
			if(a[mid] % d > a[r] % d && a[mid] % d > a[mid + 1] % d) {
				r = mid;
			} else {
				l = mid;
			}
		}
		return r;
	}
} // 完整凸包二分求极值
