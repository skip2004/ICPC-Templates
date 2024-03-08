std::vector<p2> gethull(std::vector<p2> o) {
	sort(o.begin(), o.end(), [](p2 x, p2 y) {
		if(x.x == y.x) {
			return x.y > y.y; // gt => lt
		} else {
			return x.x < y.x;
		}
	});
	std::vector<p2> stack;
	for(p2 x : o) {
		if(stack.size() && stack.back().x == x.x) {
			continue;
		}
		for(;stack.size() >= 2 && cross(stack.rbegin()[1], stack.back(), x) >= 0;) { // gt => lt
			stack.pop_back();
		}
		stack.push_back(x);
	}
	return stack;
}
