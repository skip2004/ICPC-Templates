// https://loj.ac/s/2042359
#include <bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;

cs int N = 1 << 20 | 5;

char S[N];
int n;
vector <int> duval(char *S) { 
	int i = 0, j, k, s = strlen(S); vector <int> ans; 
	while(i < s) {
		j = i, k = i + 1; 
		while(j < s && k < s && S[j] <= S[k]) {
			if(S[j] == S[k]) ++ j; 
			else j = i; ++ k; 
		} while (i <= j) { ans.pb(i + k - j - 1); i += k - j; }
	} return ans;  // [ans[i] + 1, ans[i + 1]] is a lyndon word  
} 
// vector <int> duval(char * S) { // vector <int> S 
//     int i = 0, j, k;
//     vector <int> ans; 
//     while(i < n) {
//         j = i, k = i + 1; 
//         while(j < n && k < n && S[j] <= S[k]) {
//             if(S[j] == S[k]) ++ j; 
//             else j = i; ++ k; 
//         }
//         while (i <= j) {
//             ans.pb(i + k - j - 1);
//             i += k - j; 
//         }
//     } return ans;  // [ans[i] + 1, ans[i + 1]] is a lyndon word  
// } 
int main() {
    #ifdef zqj 
    freopen("1.in","r",stdin);
    #endif
    scanf("%s", S); 
    n = strlen(S);
    vector <int> lyn = duval(S);
    for(int x : lyn) cout << x + 1 << ' ';
    return 0; 
}