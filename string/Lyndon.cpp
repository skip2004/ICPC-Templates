for(int i=1; i<=n;) {
	int j=i, k=i+1;
	while(S[j]<=S[k]){
		if(S[j]==S[k]) ++j;
		else j=i; ++k;
	}
	while(i<=j){
		printf("%d ",i+k-j-1);
		i+=k-j;
	}
} 
