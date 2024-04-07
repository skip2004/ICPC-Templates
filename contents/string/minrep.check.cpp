// https://www.luogu.com.cn/record/154725048
#include <bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;

cs int N = 1 << 20 | 5;

char S[N];
int n;
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
int main() {
    #ifdef zqj 
    freopen("1.in","r",stdin);
    #endif
    cin >> n; 
    vector <int> S(n);
    for(int i = 0; i < n; ++ i) scanf("%d", & S[i]);
    vector <int> ans = min_rep(S);
    for(int x : ans) cout << x << ' '; 
    return 0; 
}