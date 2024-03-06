int root,cc;
struct hh{int w,pri,ch[2],size;}tr[sz];
#define ls(x) tr[x].ch[0]
#define rs(x) tr[x].ch[1]
void pushup(int x){tr[x].size=1+tr[ls(x)].size+tr[rs(x)].size;}
int newnode(int w) {
	++cc;
	tr[cc].w=w,tr[cc].pri=rnd(1,int(1e9)),tr[cc].size=1;
	return cc;
}
int merge(int x,int y) {
	if (!x||!y) return x+y;
	if (tr[x].pri<tr[y].pri) return rs(x)=merge(rs(x),y),pushup(x),x;
	return ls(y)=merge(x,ls(y)),pushup(y),y;
}
void split(int x,int w,int &a,int &b) {
	if (!x) return a=b=0,void();
	if (tr[x].w<=w) a=x,split(rs(x),w,rs(x),b);
	else b=x,split(ls(x),w,a,ls(x));
	pushup(x);
}
