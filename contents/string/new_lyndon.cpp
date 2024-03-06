vector <int> duval(vector <int> S) { 
	int i = 0, j, k, s = S.size(); vector <int> ans; 
	while(i < s) {
		j = i, k = i + 1; 
		while(j < s && k < s && S[j] <= S[k]) {
			if(S[j] == S[k]) ++ j; 
			else j = i; ++ k; 
		} while (i <= j) { ans.pb(i + k - j - 1); i += k - j; }
	} return ans;  // [ans[i] + 1, ans[i + 1]] is a lyndon word  
} 
vector <int> min_rep(vector <int> S) {
	int k = 0, i = 0, j = 1, n = size(S);
	while (k < n && i < n && j < n) {
		if (S[(i + k) % n] == S[(j + k) % n]) k ++;
		else {
			S[(i + k) % n] > S[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
			if (i == j) i ++; k = 0;
		}
	} i = min(i, j);
	rotate(S.begin(), S.begin() + i, S.end()); return S; 
}
