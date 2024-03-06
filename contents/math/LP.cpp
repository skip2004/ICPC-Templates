using db = long double;
const db eps = 1e-16;
int sgn(db x) { return x < -eps ? -1 : x > eps; }
namespace LP {
	const int N = 21, M = 21;
	int n, m; // n : 变量个数，m : 约束个数
	db a[M + N][N], x[N + M];
	// 约束：对于 1 <= i <= m : a[i][0] + \sum_j x[j] * a[i][j] >= 0
	// x[j] >= 0
	// 最大化 \sum_j x[j] * a[0][j]
	int id[N + M];
	void pivot(int p, int o) {
		std::swap(id[p], id[o + n]);
		db w = -a[o][p];
		for(int i = 0;i <= n;++i) a[o][i] /= w;
		a[o][p] = -1 / w;
		for(int i = 0;i <= m;++i) if(sgn(a[i][p]) && i != o) {
			db w = a[i][p]; a[i][p] = 0;
			for(int j = 0;j <= n;++j) a[i][j] += w * a[o][j];
		}
	}
	db solve() { // nan : 无解，inf : 无界，否则返回最大值
		for(int i = 1;i <= n + m;++i) id[i] = i;
		for(;;) {
			int p = 0, min = 1;
			for(int i = 1;i <= m;++i) {
				if(a[i][0] < a[min][0]) min = i;
			}
			if(a[min][0] >= -eps) break;
			for(int i = 1;i <= n;++i) if(a[min][i] > eps && id[i] > id[p]) {
				p = i;
			}
			if(!p) return nan("");
			pivot(p, min);
		}
		for(;;) {
			int p = 1;
			for(int i = 1;i <= n;++i) if(a[0][i] > a[0][p]) p = i;
			if(a[0][p] < eps) break;
			db min = INFINITY; int o = 0;
			for(int i = 1;i <= m;++i) if(a[i][p] < -eps) {
				db w = -a[i][0] / a[i][p]; int d = sgn(w - min);
				if(d < 0 || !d && id[i] > id[o]) o = i, min = w;
			}
			if(!o) return INFINITY;
			pivot(p, o);
		}
		for(int i = 1;i <= m;++i) x[id[i + n]] = a[i][0];
		return a[0][0];
	}
}
