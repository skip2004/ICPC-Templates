int c[N][26], mx[N], fail[N], tot = 1;
int append(int id, int w) {
	int p = id, now = ++ tot;
	//right[now] = id;
	for(mx[now] = mx[p] + 1;p && !c[p][w];p = fail[p])
		c[p][w] = now;
	if(!p) fail[now] = 1;
	else {
		int q = c[p][w];
		if(mx[q] == mx[p] + 1) fail[now] = q;
		else {
			int x = ++ tot; mx[x] = mx[p] + 1;
			memcpy(c[x], c[q], sizeof(c[0])), fail[x] = fail[q]; //right[x] = right[q];
			for(fail[q] = fail[now] = x;p && c[p][w] == q;p = fail[p])
				c[p][w] = x;
		}
	}
	return now;
}
void buildtree() { // 倒着建
	for(int i = 2;i <= tot;++i)
		son[fa[i]][s[right[i] + mx[fa[i]]] - 'a'] = i;
}
