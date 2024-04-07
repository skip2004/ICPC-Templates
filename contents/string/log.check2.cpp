// https://loj.ac/s/2042355
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int MAXN = 2e5 + 5;
typedef long long ll;
typedef long double ld;
// typedef unsigned long long u128;
typedef __uint128_t u128;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
namespace Hash {
	const int MAXN = 2e5 + 5;
	const int P = 1e9 + 7;
	int n, block, tot, l[MAXN], r[MAXN];
	int belong[MAXN], val[MAXN], inc[MAXN];
	u128 pre[MAXN], tag[MAXN], base[MAXN], sbase[MAXN];
	void init(int x) {
		n = x, block = sqrt(n);
		for (int i = 1; i <= n; i++) {
			if (i % block == 1 % block) l[++tot] = i;
			belong[i] = tot, r[tot] = i;
		}
		base[0] = sbase[0] = 1;
		for (int i = 1; i <= n; i++) {
			read(val[i]), val[i] += 5e8;
			base[i] = base[i - 1] * P;
			sbase[i] = sbase[i - 1] + base[i];
			pre[i] = pre[i - 1] + base[i] * val[i];
		}
	}
	int value(int pos) {
		return val[pos] + inc[belong[pos]];
	}
	u128 query(int pos) {
		return pre[pos] + tag[belong[pos]] + inc[belong[pos]] * (sbase[pos] - sbase[l[belong[pos]] - 1]);
	}
	void modify(int ql, int qr, int d) {
		if (belong[ql] == belong[qr]) {
			for (int i = ql; i <= qr; i++) {
				val[i] += d;
				pre[i] += d * (sbase[i] - sbase[ql - 1]);
			}
		} else {
			for (int i = ql; i <= r[belong[ql]]; i++) {
				val[i] += d;
				pre[i] += d * (sbase[i] - sbase[ql - 1]);
			}
			for (int i = l[belong[qr]]; i <= qr; i++) {
				val[i] += d;
				pre[i] += d * (sbase[i] - sbase[ql - 1]);
			}
			for (int i = belong[ql] + 1; i <= belong[qr] - 1; i++) {
				inc[i] += d;
				tag[i] += d * (sbase[l[i] - 1] - sbase[ql - 1]);
			}
		}
		u128 change = d * (sbase[qr] - sbase[ql - 1]);
		for (int i = qr + 1; i <= r[belong[qr]]; i++)
			pre[i] += change;
		for (int i = belong[qr] + 1; i <= tot; i++)
			tag[i] += change;
	}
	int lcp(int x, int y) {
		if (x > y) swap(x, y);
		int l = 0, r = n - y + 1, delta = y - x;
		u128 lx = query(x - 1);
		u128 ly = query(y - 1);
		while (l < r) {
			int mid = (l + r + 1) / 2;
			if ((query(x + mid - 1) - lx) * base[delta] == query(y + mid - 1) - ly) l = mid;
			else r = mid - 1;
		}
		return l;
	}
	void debug() {
		for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			cerr << i << ' ' << j << ' ' << lcp(i, j) << endl;
		cerr << endl;
	}
}
struct info {
	int l, r;
	vector <int> points;
};
void work(vector <int> St, vector <int> & nx, int r) {
    for(int x : St){
	    bool FLAG = true;
        while(nx.size()){
            int y = nx.back(); 
            int lcp = Hash :: lcp(x, y); 
            if(x + lcp - 1 >= r) break;
            if(Hash :: value(x + lcp) > Hash :: value(y + lcp)) { 
                FLAG = false; break; 
            } 
            nx.pop_back();
        } 
        if(FLAG && (nx.empty() || r - x + 1 <= x - nx.back())) nx.pb(x);
    }
}
info operator + (info a, info b) {
	assert(a.r == b.l - 1);
	info ans;
	ans.l = a.l, ans.r = b.r;
	ans.points.clear();

    work(a.points, ans.points, b.r);
    work(b.points, ans.points, b.r);
    return ans;
}
struct SegmentTree {
	struct Node {
		int lc, rc;
		info ans;
	} a[MAXN * 2];
	int n, root, size;
	void update(int root) {
		a[root].ans = a[a[root].lc].ans + a[a[root].rc].ans;
	}
	void build(int &root, int l, int r) {
		root = ++size;
		if (l == r) {
			a[root].ans.l = l;
			a[root].ans.r = r;
			a[root].ans.points.clear();
			a[root].ans.points.push_back(l);
			return;
		}
		int mid = (l + r) / 2;
		build(a[root].lc, l, mid);
		build(a[root].rc, mid + 1, r);
		update(root);
	}
	void init(int x) {
		n = x;
		root = size = 0;
		build(root, 1, n);
	}
	void modify(int root, int l, int r, int ql, int qr) {
		if (l == ql && r == qr) return;
		int mid = (l + r) / 2;
		if (mid >= ql) modify(a[root].lc, l, mid, ql, min(qr, mid));
		if (mid + 1 <= qr) modify(a[root].rc, mid + 1, r, max(mid + 1, ql), qr);
		update(root);
	}
	void modify(int l, int r) {
		if (l > r) return;
		else modify(root, 1, n, l, r);
	}
	info query(int root, int l, int r, int ql, int qr) {
		if (l == ql && r == qr) return a[root].ans;
		int mid = (l + r) / 2;
		if (mid >= qr) return query(a[root].lc, l, mid, ql, qr);
		if (mid + 1 <= ql) return query(a[root].rc, mid + 1, r, ql, qr);
		return query(a[root].lc, l, mid, ql, mid) + query(a[root].rc, mid + 1, r, mid + 1, qr);
	}
	int query(int l, int r) {
		if (l > r) return -1;
		else return query(root, 1, n, l, r).points.back();
	}
} ST;
int n, q;
int main() {
    #ifdef zqj
    freopen("1.in", "r", stdin);
    #endif
	read(n), read(q);
	Hash :: init(n), ST.init(n);
	for (int i = 1; i <= q; i++) {
		int opt, l, r;
		read(opt), read(l), read(r);
		if (opt == 1) {
			int x; read(x);
			Hash :: modify(l, r, x);
			ST.modify(l, r);
		} else writeln(ST.query(l, r));
	}
	return 0;
}