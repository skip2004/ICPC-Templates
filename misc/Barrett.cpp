struct DIV {
	u64 x;
	void init(u64 v) { x = -1ull / v + 1; }
};
// works while x*(y-1)<2^64
u64 operator / (const u64 & x, const DIV & y) {
	return (u128) x * y.x >> 64;
}
