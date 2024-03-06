#include<bits/stdc++.h>
using std::cin;
using std::cout;
using u64 = unsigned long long;
using i64 = long long;
using u128 = __uint128_t;
inline u64 d(u64 x) {
	u64 d = 1;
	for(int i = 2;i * i <= x;++i) if(x % i == 0) {
		int c = 0;
		do {
			x /= i;
			++ c;
		} while(x % i == 0);
		d *= c + 1;
	}
	if(x > 1)
		d *= 2;
	return d;
}
std::vector<u128> pr;
using PUU = std::pair<u64, u64>;
std::priority_queue<PUU, std::vector<PUU>, std::greater<PUU>> Q;
inline void push(u128 x) {
	if(x <= 2e18) {
		Q.emplace(x, d(x));
	}
}
inline std::string SN(u64 x, int d = 10) {
	double w = x;
	int z = 0;
	for(;w >= d;) {
		w /= d;
		++ z;
	}
	char buf[10];
	sprintf(buf, "%.2lf", w);
	return (std::string)buf + "\\times " + std::to_string(d) + "^{" + std::to_string(z) + "}";
}
inline std::string factor(u64 x) {
	if(x == 1)
		return "1";
	std::map<u64, int> f;
	u64 d = 1;
	for(int i = 2;i * i <= x;++i) if(x % i == 0) {
		do {
			x /= i;
			f[i] += 1;
		} while(x % i == 0);
	}
	if(x > 1)
		f[x] += 1;
	std::string res;
	for(auto [a, b] : f) {
		if(!res.empty())
			res += "\\cdot";
		res += std::to_string(a);
		if(b > 1)
			res += "^{" + std::to_string(b) + "}";
	}
	return res;
}
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	for(int i = 2;i <= 100;++i)
		if(d(i) == 2) pr.push_back(i);
	Q.emplace(d(1), 1);
	u64 max_pre = 0;
	std::map<u64, PUU> map;
	for(u64 i = 2;i <= 2e18;i += i) map[i];
	for(u64 i = 10;;i *= 10) {
		map[i];
		if(i == 1e18) break;
	}
	for(;Q.size();) {
		auto x = Q.top();
		Q.pop();
		if(x.second <= max_pre) {
			continue;
		}
		max_pre = x.second;
		map.lower_bound(x.first) -> second = x;
		int i = 0;
		while(x.first % pr[i] == 0) 
			push(x.first * pr[i]), ++i;
		push(x.first * pr[i]);
	}
	cout << "|n|factor|d(n)|\n";
	cout << "|-|-|-|\n";
	for(auto [tmp, x] : map) {
		if(x.first)
			cout << "|$" << x.first << "=" << SN(x.first) << "=" << SN(x.first, 2) << "$|$" << factor(x.first) << "$|$" << x.second << "$|\n";
	}
}
