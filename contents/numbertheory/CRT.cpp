ll CRT(ll a1, ll p1, ll a2, ll p2) {
	ll a, b, gcd = std::gcd(p1, p2);
	if((a1 - a2) % gcd) 
		return -1;
	exgcd(p1, p2, a, b);
	ll k = i128((a2 - a1) % p2 + p2) * (a + p2) % p2;
	return p1 / gcd * k + a1;
}
