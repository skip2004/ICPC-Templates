for(int i = 1; i <= n; i ++) {
	St.pb(i); vector<int> nw;
	for(auto t : St) {
		bool ok = true;
		while(!nw.empty()){
			int x = nw.back();
			if(S[i] > S[i-t+x]) ok = false;
			if(S[i] >= S[i-t+x]) break; nw.pop_back();
		} 
		if(ok && (nw.empty() || (i-t<=t-nw.back()))) nw.pb(t);
	} St = nw;
}
for(int x : St){
	bool FLAG = true;
	while(nx.size()){
		int y = nx.back(); int lcp = LCP(x, y); if(x + lcp - 1 >= r) break;
		if(S[x + lcp] > S[y + lcp]){ FLAG = false; break; } nx.pop_back();
	} if(FLAG && (nx.empty() || r - x + 1 <= x - nx.back())) nx.pb(x);
}
