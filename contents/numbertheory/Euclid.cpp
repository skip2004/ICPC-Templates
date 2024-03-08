// 万欧
// 前提 : r < q, r >= q 先提几个 U 出来再用
// 使用：Y * q <= X * p + r, 斜率 p/q, U表示向上，R表示到达一个顶点，先一些 U 再一个 R
template<class T>
T power(T a, ll k) {
	// 有效率需求可以改为半群乘法
	if(!k) return T();
	T res = a;
	for(--k;k;) {
		if(k & 1) res = res + a;
		if(k >>= 1) a = a + a;
	}
	return res;
}
template<class T>
T solve(ll p, ll q, ll r, ll l, T U, T R) {
	if (p >= q)
		return solve(p % q, q, r, l, U, power(U, p / q) + R);
	ll m = ((__int128)p * l + r) / q;
	if (!m) return power(R, l);
	ll cnt = l - ((__int128)q * m - r - 1) / p;
	return power(R, (q - r - 1) / p) + U + solve(q, p, (q - r - 1) % p, m - 1, R, U) + power(R, cnt);
}
