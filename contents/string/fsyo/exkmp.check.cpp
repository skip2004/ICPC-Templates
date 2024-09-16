// https://www.luogu.com.cn/record/154721794
#include<bits/stdc++.h>
#define cs const
using namespace std;
cs int N = 2e7 + 50;
typedef long long ll;
char S[N+N], T[N]; int n, m;
int main(){
	#ifdef FSYo
	freopen("1.in","r",stdin);
	#endif
	scanf("%s%s",T+1,S+1); m=strlen(S+1);
	strcat(S+1,"#"); strcat(S+1,T+1); n=strlen(S+1); 
    static int lcp[N+N]; 
    int mx=1, pt=1; lcp[1]=n;
    for(int i=2; i<=n; i++){
        if(i<=mx) lcp[i]=min(lcp[i-pt+1],mx-i+1);
        while(i+lcp[i]<=n && S[i+lcp[i]]==S[1+lcp[i]]) ++lcp[i];
        if(i+lcp[i]-1>mx) pt=i, mx=i+lcp[i]-1;
    } 

	ll a=0, b=0; lcp[1]=m;
	for(int i=1; i<=n; i++){
		if(i<=m) b^=(ll)i*(lcp[i]+1);
		else if(S[i]!='#') a^=(ll)(i-m-1)*(lcp[i]+1);
	} cout<<b<<'\n'<<a; return 0;
}