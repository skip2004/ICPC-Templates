//https://www.luogu.com.cn/record/154721515 
#include<bits/stdc++.h>

using ll = long long;
using i128 = __int128;
using std::cin;
using std::cout;
void exgcd(ll a, ll b, ll & x, ll & y) {
	if(!b) return x = 1, y = 0, void();
	exgcd(b, a % b, y, x), y -= a / b * x;
}

ll exCRT(ll a1, ll p1, ll a2, ll p2) {
	ll a, b, gcd = std::gcd(p1, p2);
	if((a1 - a2) % gcd) 
		return -1;
	exgcd(p1, p2, a, b);
	ll k = i128((a2 - a1) % p2 + p2) * (a + p2) % p2;
	return p1 / gcd * k + a1;
}

int main() {
	int n;
	cin >> n;
	ll a = 0, p = 1;
	for(int i = 0;i < n;++i) {
		ll x, y;
		cin >> y >> x;
		a = exCRT(a, p, x, y);
		p = std::lcm(p, y);
	}
	cout << a << '\n';
}
