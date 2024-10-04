int c[N][26], fail[N], len[N], tot;
void init() {
	fail[0] = 1, len[++tot] = -1;
	// root is 1
}
int get_fail(int o, char * x) {
	for(;*x != x[-len[o] - 1];)
		o = fail[o];
	return o;
}
int append(int o, char * x) {
	o = get_fail(o, x);
	int & p = c[o][*x - 'a'];
	if(!p) {
		fail[++tot] = c[get_fail(fail[o], x)][*x - 'a'];
		len[p = tot] = len[o] + 2;
	}
	return p;
}
