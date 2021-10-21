/*
NTT params : 
p				g	r	k
998244353 		3 	119 23
2013265921	 	31 	15 	27
206158430281 	7 	15 	37

How to NTT : 
1. w(n, m) <- a^m, w(n / 2, m) = a^2m
2. p = (2^k) * r + 1
3. we have : g ^ (p - 1) = 1
4. we need : a^(2^k) = 1
5. thus a = g^r(cycle size = 2^k) 
*/

struct FFT {
	int n, k;
	const double PI = acos(-1);
	const cp I = cp(0, 1);
	vector<int> rev;
	vector<cp> omega, iomega;
	void init_(int _n) {
		assert(__builtin_popcount(_n));
		n = _n, k = 31 - __builtin_clz(n);
		rev.assign(n, 0);
		rep(i, 0, n - 1) {
			rep(j, 0, k) if((i >> j) & 1) 
				rev[i] |= (1 << (k - j));
		}
		cp w = exp(2. * PI / (double) n * I);
		cp iw = exp(-2. * PI / (double) n * I)
		omega.assign(n, 1);
		iomega.assign(n, 1);
		rep(i, 1, n - 1) {
			omega[i] = omega[i - 1] * w;
			iomega[i] = iomega[i - 1] * iw;
		}
	}
	void transform(vector<cp> &a, cp* b) {
		rep(i, 0, n - 1) if(i > rev[i])
			swap(a[i], a[rev[i]]);
		rep(l, 1, k) {
			int len = (1 << l), mid = (1 << (l - 1));
			for(int i = 0; i < n; i += len) {
				rep(j, 0, mid - 1) {
					cp t = a[i + j + mid] * b[i + j];
					a[i + j + mid] = a[i + j] - t;
					a[i + j] = a[i + j] + t;
				}
			}
		} 
	}
	void fft(bool inv, vector<cp> &a) { 
		transform(a, (inv ? iomega : omega));
		rep(i, 0, n - 1) a[i] /= n; 
	}
};

