for(int i = 2; i <= T[0].nd; i++) {
	int x = T[0].A[i];
	int R = T[0].r[x], L = R - T[0].len[x] + 1; 
	int y = T[1].fnd(T[1].ed[L], R - L + 1);
	if(T[1].len[y] == R - L + 1) {
		++ cnt; T[0].tag[x] = cnt; T[1].tag[y] = cnt; 
		rt[0][cnt] = x, rt[1][cnt] = y; 
	}
}
for(int o = 0; o < 2; o++)
for(int i = T[o].nd; i > 1; i--) {
	int x = T[o].A[i];
	if(T[o].tag[x]) continue;
	for(int k = 0; k < 26; k++)
		if(T[o].ch[x][k]) T[o].tag[x] = T[o].tag[T[o].ch[x][k]];
}
for(int o = 0; o < 2; o++)
for(int i = 2; i <= T[o].nd; i++) {
	int x = T[o].A[i];
	vec[o][T[o].tag[x]].pb(x);
} // vec[0] : from left to right, node id of the colunm , vec[1] : from down to up
// U : T[0].r[rt] - T[0].len[rt] + 1, D = U + vec[1][t].size() - 1, L = R - vec[0][t].size() + 1, R = T[0].r[rt]
int x = T[0].fnd(T[0].ed[r], r - l + 1);
int blk = T[0].tag[x];
// distance to the right , 0 - base 
int rp = T[0].r[rt[0][blk]] - T[0].r[x];
// distance to the up // the upper - right point is (T[0].r[rt] - T[0].len[rt] + 1, T[0].r[rt]) 
int lp = T[0].r[x] - (r - l) - (T[0].r[rt[0][blk]] - T[0].len[rt[0][blk]] + 1);
