#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) for(int i = a; i <= b; i++)

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9) 

using namespace std;
#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	vector<vector<int>> dp1, dp2;
	void add(int &a, int b) {
		a = (a + b) % MOD;
		if(a >= MOD) a -= MOD;
	}
	int solve(int n, int k) {
		dp1.assign(n + 1, vector<int>(n + 1, 0));
		dp2.assign(n + 1, vector<int>(n + 1, 0));
		dp1[1][0] = 1;
		rep(i, 0, n) rep(j, 0, i - 1) {
			int cur = dp1[i][j];
			if(i + 1 <= n && j + 1 <= n) add(dp1[i + 1][j + 1], cur);
			if(i + 1 <= n && j - 1 >= 0) add(dp1[i + 1][j - 1], j * cur);
			if(i + 1 <= n) add(dp1[i + 1][j], cur * (i - j));			
		}
		dp2[0][0] = 1;
		rep(i, 1, n) {
			int sum = 0;		
			rep(j, 1, n) {
				add(sum, dp2[i - 1][j - 1]);
				dp2[i][j] = sum;
				if(j - k >= 0) add(sum, -dp2[i - 1][j - k]);
			}
		}
		int ans = 0;
		rep(i, 1, n) add(ans, dp1[i][0] * dp2[i][n]);
		return (ans % MOD + MOD ) %MOD;
	} 
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	cout << solve(n, k) << "\n";	
	return 0;
}
