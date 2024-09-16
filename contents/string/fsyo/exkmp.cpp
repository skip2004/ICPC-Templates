static int lcp[N]; 
int mx=1, pt=1; lcp[1]=n;
for(int i=2; i<=n; i++){
	if(i<=mx) lcp[i]=min(lcp[i-pt+1],mx-i+1);
	while(i+lcp[i]<=n && S[i+lcp[i]]==S[1+lcp[i]]) ++lcp[i];
	if(i+lcp[i]-1>mx) pt=i, mx=i+lcp[i]-1;
} 
