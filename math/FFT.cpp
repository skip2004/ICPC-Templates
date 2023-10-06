using db = double;
using cp = std::complex<db>;
// cp::real, cp::imag, std::conj, std::arg
const db pi = std::acos(-1);
int rev[N], lim;
cp wn[N];
void init(int len) {
	lim = 2 << std::__lg(len - 1);
	for(static int i = 1;i < lim;i += i) {
		for(int j = 0;j < i;++j) {
			wn[i + j] = std::polar(1., db(j) / i * pi);
		}
	}
	for(int i = 1;i < lim;++i) {
		rev[i] = rev[i >> 1] >> 1 | (i % 2u * lim / 2);
	}
}
void DFT(cp * a) {
	for(int i = 0;i < lim;++i) {
		if(rev[i] < i) std::swap(a[rev[i]], a[i]);
	}
	for(int i = 1;i < lim;i += i) {
		for(int j = 0;j < lim;j += i + i) {
			for(int k = 0;k < i;++k) {
				cp x = a[i + j + k] * wn[i + k];
				a[i + j + k] = a[k + j] - x;
				a[k + j] += x;
			}
		}
	}
}
void IDFT(cp * a) {
	DFT(a), std::reverse(a + 1, a + lim);
	for(int i = 0;i < lim;++i)
		a[i] /= lim;
}
