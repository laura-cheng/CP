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
namespace solver {
	int n, m;
	vector<int> x, y, z;
	vector<vector<int>> dp;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		x.assign(m, 0);
		y.assign(m, 0);
		z.assign(m, 0);
		dp.assign(n + 1, vector<int>((1 << n), 0));
	}
	int solve() {
		dp[0][0] = 1;
		rep(i,1, n) {
			rep(j, 0, (1 << n) - 1) {
				if(__builtin_popcount(j) != i) continue;
				bool good = 1;
				rep(k, 0, m - 1) {
					if(x[k] < i) continue;
					int cur = j & ((1 << y[k]) - 1);
					good &= (__builtin_popcount(cur) <= z[k]);
				}
				if(!good) continue;
				rep(k, 0, n - 1) if((j >> k) & 1) {
					dp[i][j] += dp[i - 1][j ^ (1 << k)];
				}
			}
		}
		return dp[n][(1 << n) - 1];
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 0, m - 1) {
		cin >> x[i] >> y[i] >> z[i];
	}
	cout << solve() << "\n";
	return 0;
}
