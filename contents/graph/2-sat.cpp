rep(i,1,n) if (bel[i<<1]==bel[i<<1|1]) return puts("IMPOSSIBLE"),0;
puts("POSSIBLE");
rep(i,1,n) printf("%d ",bel[i<<1]>bel[i<<1|1]);
