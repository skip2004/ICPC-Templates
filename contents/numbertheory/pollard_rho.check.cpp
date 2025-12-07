//https://www.luogu.com.cn/record/154722354 
#include<bits/stdc++.h>
using std::cout;
using std::cin;
using ll = long long;
using f64 = long double;

ll p;
f64 invp;
void setmod(ll x) {
	p = x, invp = (f64) 1 / x;
}
ll mul(ll a, ll b) {
	ll z = a * invp * b + 0.5;
	ll res = a * b - z * p;
	return res + (res >> 63 & p);
}
ll pow(ll a, ll x, ll res = 1) {
	for(;x;x >>= 1, a = mul(a, a))
		if(x & 1) res = mul(res, a);
	return res;
}
bool checkprime(ll p) {
	if(p == 1) return 0;
	setmod(p);
	ll d = __builtin_ctzll(p - 1), s = (p - 1) >> d;
	for(ll a : {2, 3, 5, 7, 11, 13, 82, 373}) {
		if(a % p == 0)
			continue;
		ll x = pow(a, s), y;
		for(int i = 0;i < d;++i, x = y) {
			y = mul(x, x);
			if(y == 1 && x != 1 && x != p - 1)
				return 0;
		}
		if(x != 1) return 0;
	}
	return 1;
}

#include"pollard_rho.cpp"
int main() {
	std::ios::sync_with_stdio(false), cin.tie(0);
	int T; cin >> T;
	for(int i = 0;i < T;++i) {
		ll x; cin >> x;
		auto res = factor(x);
		if(res.size() > 1) {
			cout << res.back() << '\n';
		} else {
			cout << "Prime" << '\n';
		}
	}
}
