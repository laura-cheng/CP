#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace sub1 {
	int n, m, k, s;
	vector<int> R[2], C[2];
	void init_(int _n, int _m, int _k, int _s) {
		n = _n, m = _m, k = _k, s = _s;
		R[0].assign(n + 1, 0);
		R[1].assign(n + 1, 0);
		C[0].assign(m + 1, 0);
		C[1].assign(m + 1, 0);
	}
	void add(int &a, int b) {
		a = (a + b) % MOD;
	}
	int solve() {
		R[0][0] = 1, C[0][0] = 1;
		rep(i, 1, k) {
			int id = i & 1;
			rep(j, 0, n) R[id][j] = 0;
			rep(j, 0, m) C[id][j] = 0; 
			R[id][0] = R[!id][1];
			R[id][n] = R[!id][n - 1];
			
			C[id][0] = C[!id][1];
			C[id][m] = C[!id][m - 1];
			
			rep(j, 1, n - 1) {
				add(R[id][j], R[!id][j - 1] * (n - j + 1) 
					+ R[!id][j + 1] * (j + 1));
			} 
			rep(j, 1, m - 1) {
				add(C[id][j], C[!id][j - 1] * (m - j + 1) 
					+ C[!id][j + 1] * (j + 1));
			}
		}
		int ans = 0;
		rep(i, 0, n) {
			rep(j, 0, m) {
				int cur = i * m - j * i + j * (n - i);
				if(cur == s) add(ans, R[k & 1][i] * C[k & 1][j]);
			}
		}
		return ans;
	}
};
using namespace sub1;

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n, m, k, s;
		cin >> n >> m >> k >> s;
		init_(n, m, k, s);
		cout << solve() << "\n";
	}
	
	return 0;
} 
