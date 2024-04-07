//https://www.luogu.com.cn/record/154723301
#include<bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
cs int N = 3e6 + 50;
typedef long long ll;
char S[N];
int n; 
int main(){
	#ifdef zqj
	freopen("1.in","r",stdin);
	#endif
    scanf("%s", S + 1);
    n = strlen(S + 1);
    static int lcp[N]; 
    int mx = 1, pt = 1; lcp[1] = n; 
    for(int i = 2; i <= n; i++) {
        if(i <= mx) lcp[i] = min(lcp[i - pt + 1], mx - i + 1);
        while(i + lcp[i] <= n && S[i + lcp[i]] == S[1 + lcp[i]]) ++ lcp[i];
        if(i + lcp[i] - 1 > mx) pt = i, mx = i + lcp[i] - 1; 
    }
    // for(int i = 1; i <= n; i++) cout << lcp[i] << ' ';cout<<endl;
    vector <int> st; 
    for(int i = 1; i <= n; i++) {
        st.pb(i);
        vector <int> nx; 
        for(int t : st) {
            bool ok = true; 
            while(!nx.empty()) {
                int x = nx.back();
                if(S[i] > S[i - t + x]) ok = false; 
                if(S[i] >= S[i - t + x]) break;
                nx.pop_back();
            }
            if(ok && (nx.empty() || (i - t + 1 <= t - nx.back())))
                nx.pb(t);
        } 
        st = nx; 
        // cout << "FFF : ";
        // for(int x : st) cout << x << ' ';cout << '\n';
        int p = st[0];
        for(int j = 1; j < st.size(); j++) {
            int q = st[j];
            // p -- i, 1 -- p - 1
            // q -- i, 1 -- q - 1
            // p + i - q + 1 -- i, 
            int len = lcp[p + i - q + 1];
            // cout <<p << ' ' << q << endl;
            if(p + i - q + 1 + len <= i) {
                if(S[p + i - q + 1 + len] > S[1 + len]) {
                    p = q;
                }
            }
            else {
                // 1 ... p - 1
                // q - p + 1 .. 
                int len = lcp[q - p + 1];
                if(1 + len <= p - 1) {
                    if(S[1 + len] > S[q - p + 1 + len]) {
                        p = q; 
                    }
                }
            }
        }
        cout << p << ' ';
    }
    cout << '\n';
    return 0;
}