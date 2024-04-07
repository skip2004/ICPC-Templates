#include<bits/stdc++.h>
using ll = long long;
// result : -b < x < b AND -a < y <= a when a,b != 0
void exgcd(ll a, ll b, ll & x, ll & y) {
	if(!b) return x = 1, y = 0, void();
	exgcd(b, a % b, y, x), y -= a / b * x;
}
int main() {
	const int N = 10000;
	for(int i = 0;i < N;++i) {
		for(int j = !i;j < N;++j) {
			ll x, y;
			exgcd(i, j, x, y);
			if(i && j) {
				assert(-j < x && x < j);
				assert(-i < y && y <= i);
			}
			assert(i * x + j * y == std::gcd(i, j));
		}
	}
}
