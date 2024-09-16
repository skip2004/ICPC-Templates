S[1] = '%';
for(int i = 1; i <= len; i++){
	S[i << 1] = '&'; 
	S[i << 1|1] = s[i];
} 
len = len << 1 | 1;
S[++len] = '&';
S[++len] = '$';
int mx = 0, id = 0, ans = 0;
for(int i = 1; i <= len; i++){
	if(mx > i) p[i] = min(p[id * 2 - i], mx - i);
	else p[i] = 1;
	while(S[i - p[i]] == S[i + p[i]]) ++p[i];
	if(i + p[i] > mx) id = i, mx = i + p[i];
	ans = max(ans, p[i] - 1);
}
