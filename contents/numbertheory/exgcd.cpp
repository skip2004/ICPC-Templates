void exgcd(ll a, ll b, ll & x, ll & y) {
	if(!b) return x = 1, y = 0, void();
	exgcd(b, a % b, y, x), y -= a / b * x;
}
