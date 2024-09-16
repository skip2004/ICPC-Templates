// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define N 100050
using namespace std;

int n, q;
char s[N];  
int st[N][20],Log[N];
struct Node{
	int ls,rs,val;
}t[N*30]; int rt[N],tot;

int m, rk[N * 2], sa[N], tmp[N * 2], h[N], y[N];
void Sort(){
    static int c[N];
	for(int i=1;i<=m;i++) c[i] = 0;
	for(int i=1;i<=n;i++) c[rk[i]]++;
	for(int i=1;i<=m;i++) c[i] += c[i-1];
	for(int i=n;i>=1;i--) sa[c[rk[y[i]]]--] = y[i];
}
void get_sa(){
	for(int i=1;i<=n;i++) rk[i] = s[i], y[i] = i; Sort();
	for(int k=1;k<=n;k<<=1){
		int ret = 0;
		for(int i=n-k+1;i<=n;i++) y[++ret] = i;
		for(int i=1;i<=n;i++) if(sa[i] > k) y[++ret] = sa[i] - k;
		Sort(); 
		for(int i = 1; i <= n; i++) swap(rk[i], tmp[i]); 
		rk[sa[1]] = 1; int num = 1;
		for(int i=2;i<=n;i++){
			if(tmp[sa[i]] == tmp[sa[i-1]] && tmp[sa[i]+k] == tmp[sa[i-1]+k])
				rk[sa[i]] = num;
			else rk[sa[i]] = ++num;
		} m = num;
	}
}
void get_h(){
	int k = 0;
	for(int i=1;i<=n;i++){
		if(rk[i]==1) continue;
		int j = sa[rk[i]-1]; if(k) k--;
		while(i+k<=n && j+k<=n && s[i+k]==s[j+k]) k++;
		h[rk[i]] = k;
	}
} 


void get_ST(){
	for(int i=2;i<=n;i++) Log[i] = Log[i/2] + 1;
	for(int i=1;i<=n;i++) st[i][0] = h[i];
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			st[j][i] = min(st[j][i-1], st[j+(1<<(i-1))][i-1]);
}
int Lcp(int l,int r){
	l++; int x = Log[r-l+1];
	return min(st[l][x], st[r-(1<<x)+1][x]);
}
void Build(int &x,int l,int r){
	x = ++tot;
	if(l==r) return;
	int mid = (l+r) >> 1;
	Build(t[x].ls, l, mid);
	Build(t[x].rs, mid+1, r);
} 
void Insert(int &x,int last,int l,int r,int pos){
	x = ++tot; t[x] = t[last]; t[x].val++;
	if(l==r) return;
	int mid = (l+r) >> 1;
	if(pos<=mid) Insert(t[x].ls, t[last].ls, l, mid, pos);
	else Insert(t[x].rs, t[last].rs, mid+1, r, pos);
} 
int check(int a,int b,int l,int r,int L,int R){
	if(L<=l && r<=R) return t[b].val - t[a].val;
	int mid = (l+r) >> 1, ans = 0;
	if(L<=mid) ans += check(t[a].ls, t[b].ls, l, mid, L, R);
	if(R>mid) ans += check(t[a].rs, t[b].rs, mid+1, r, L, R);
	return ans;
}

void get_LR(int st,int len,int &L,int &R){
	int l=1,r=rk[st];
	while(l<r){
		int mid = (l+r) >> 1;
		if(Lcp(mid,rk[st])>=len) r = mid;
		else l = mid+1;
	} L = l;
	l = rk[st], r = n;
	while(l<r){
		int mid = (l+r+1) >> 1;
		if(Lcp(rk[st],mid)>=len) l = mid;
		else r = mid-1;
	} R = l;
}
int calc(int a,int b,int c,int d){
	int l = 0, r = min(b-a, d-c) + 1;
	while(l<r){
		int mid = (l+r+1) >> 1;
		int L = 0, R = 0; get_LR(c,mid,L,R);
		if(check(rt[a-1],rt[b-mid+1],1,n,L,R)) l = mid;
		else r = mid-1;
	} return l;
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("myself.out","w",stdout);
	scanf("%d%d%s",&n,&q,s+1);
	m = 127; get_sa(); get_h(); get_ST();
	Build(rt[0],1,n); 
	for(int i=1;i<=n;i++) Insert(rt[i], rt[i-1], 1, n, rk[i]);
	while(q--){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",calc(a,b,c,d));
	} return 0;
}