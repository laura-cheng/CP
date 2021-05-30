#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m;
	vector<int> a, b;
	vector<vector<int>> dp;
	void init_(int _n) {
		n =_n, m = 0;
		a.assign(n + 1, 0);
		b.assign(1, 0);
		dp.assign(n + 1, vector<int>(n + 1, INF));
	}
	int solve() {
		rep(i, 1, n) if(a[i]) {
			b.push_back(i), m ++;
		}	
		dp[0][0] = 0;
		rep(i, 1, n) rep(j, 0, m) {
			dp[i][j] = dp[i - 1][j];
			if(j && !a[i]) dp[i][j] = min(
				dp[i][j], dp[i - 1][j - 1] + abs(b[j] - i));
		}
		return dp[n][m];
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	return 0;
} 
