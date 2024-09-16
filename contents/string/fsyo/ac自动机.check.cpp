//https://www.luogu.com.cn/record/154721043
#include<bits/stdc++.h>
#define N 2000050
using namespace std;
int ch[N][26], lk[N], siz[N], tot;
int n, pos[N]; char s[N]; 
void Insert(string s, int Id){
	int len = s.length(), now = 0;
	for(int i=0; i<len; i++){
		int x = s[i] - 'a';
		if(!ch[now][x]) ch[now][x] = ++tot;
		now = ch[now][x];
	} pos[Id] = now;
}

vector<int> v[N];
void init() {
	queue <int> q; 
	for(int i = 0; i < 26; i++) 
		if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		v[lk[x]].push_back(x);
		for(int i = 0; i < 26; i++) {
			if(ch[x][i]) {
				lk[ch[x][i]] = ch[lk[x]][i];
				q.push(ch[x][i]);
			}
			else ch[x][i] = ch[lk[x]][i];
		}
	}
}

void dfs(int u){
	for(int i=0; i<v[u].size(); i++){
		int t = v[u][i]; dfs(t); siz[u] += siz[t];
	}
}
int main(){
	//freopen("1.in","r",stdin);
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		string s; cin >> s; Insert(s, i);
	} init();
	scanf("%s", s+1); int len = strlen(s+1), now = 0;
	for(int i=1; i<=len; i++){ now = ch[now][s[i] - 'a']; siz[now]++; }
	dfs(0); 
	for(int i=1; i<=n; i++) printf("%d\n", siz[pos[i]]);
	return 0;
}