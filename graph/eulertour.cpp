// 无向
	for (int &i=head[x],tmp;(tmp=i);i=edge[i].nxt)
if (!del[i>>1])
	del[i>>1]=1,dfs(v),ans[++tp]=((tmp&1)?-1:1)*(tmp>>1);
	// 有向
	for (int &i=head[x],tmp;(tmp=i);i=edge[i].nxt)
if (!del[i])
	del[i]=1,dfs(v),ans[++tp]=tmp;
