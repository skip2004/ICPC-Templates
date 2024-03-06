// Mon = 0, ... % 7
// days since 1/1/1
int getday(int y, int m, int d) {
	if(m < 3) -- y, m += 12;
	return (365 * y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307);
}
void date(int n, int & y, int & m, int & d) {
	n += 429 + ((4 * n + 1227) / 146097 + 1) * 3 / 4;
	y = (4 * n - 489) / 1461;
	n -= y * 1461 / 4;
	m = (5 * n - 1) / 153;
	d = n - m * 153 / 5;
	if (--m > 12) m -= 12, ++y;
}
