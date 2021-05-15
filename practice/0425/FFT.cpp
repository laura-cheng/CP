#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define eps (1e-9)
#define MAXN 1000005
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt199374 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace FFT {
	typedef vector<complex<lld>> poly;
	typedef complex<lld> cd;
	const lld PI = acos(-1);
	const cd I = {0, 1};
	int lg; poly A, B;
	vector<int> rev;
	vector<poly> a;
	void init_(vector<int> _a, vector<int> _b) {
		lg = 32 - __builtin_clz(_a.size() +_b.size());
		A.assign(1 << lg, {0, 0});
		B.assign(1 << lg, {0, 0});
		a.assign(1 << lg, poly());
		rep(i, 0, signed(_a.size()) - 1) A[i] = _a[i];
		rep(i, 0, signed(_b.size()) - 1) B[i] = _b[i];
		rev.assign(1 << lg, 0);
		rep(i, 0, (1 << lg) - 1) {
			rep(j, 0, lg - 1) {
				rev[i] <<= 1;
				rev[i] |= ((i >> j) & 1);
			}
		}		
	}
	poly fft(poly p, bool inv) {
		rep(i, 0, (1 << lg) - 1) a[i].assign(1, p[i]);
		rep(s, 1, lg) {
			int len = 1 << (s - 1);
			cd w = {1, 0};
			cd it_w = exp(2 * PI * I / (lld)(2 * len));
			if(inv) it_w = cd(1) / it_w;
			for(int i = 0; i < (1 << lg); i += 2 * len) a[rev[i]].resize(2 * len);
			rep(j, 0, len - 1) {
				for(int i = 0; i < (1 << lg); i += 2 * len) {
					int x = rev[i], y = rev[i + len];
					cd t = a[y][j] * w;
					a[x][j + len] = a[x][j] - t;
					a[x][j] = a[x][j] + t;
				}
				w = w * it_w;
			}	
			for(int i = len; i < (1 << lg); i += 2 * len) a[rev[i]].clear();
		}
		if(inv) for(auto &i : a[0]) i /= cd(1 << lg);
		return a[0];
	}
	vector<int> solve() {
		poly ans = poly(1 << lg, {0, 0});
		A = fft(A, 0);
		B = fft(B, 0);
		rep(i, 0, (1 << lg) - 1) ans[i] = A[i] * B[i];
		ans = fft(ans, 1);
		vector<int> ans_int;
		rep(i, 0, (1 << lg)- 1) 
			ans_int.push_back(round(abs(ans[i])));
		return ans_int;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	vector<int> a = {2, 3, 40, 500};
	vector<int> b = {40, 80, 9, 701, 2, 102};
	vector<int> c(a.size() + b.size());
	
	rep(i, 0, 3) rep(j, 0, 5) {
		c[i + j] += a[i] * b[j];
	}
	FFT::init_(a, b);
	c = FFT::solve();
	vprint(all(c));
	return 0;
}
