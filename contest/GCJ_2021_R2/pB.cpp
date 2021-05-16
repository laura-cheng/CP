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
void kout() { cerr << endl;} 
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	vector<int> dp1, dp;
	void init_() {
		dp.assign(1e6 + 1, 1);
		dp1.assign(1e6 + 1, 1);
		dp[1] = -1e9; dp[0] = -1e9; dp[2] = -1e9;
		dp1[1] = 0, dp1[0] = 0;
		rep(i, 3, 1e6) {
			int k = sqrt(i) + 1;
			rep(j, 2, k) {
				if(i % j) continue;
				dp1[i] = max(dp1[i], dp1[i / j - 1] + 1);
				dp1[i] = max(dp1[i], dp1[j - 1] + 1);
				if(j >= 3) dp[i] = max(dp[i], dp1[i / j - 1] + 1);
				if(i / j >= 3) dp[i] = max(dp[i], dp1[j - 1] + 1);
			}
		}	
	}
}; 
namespace solver1 {
	vector<vector<int>> dpp;
	vector<int> dp;
	void init_() {
		dpp.assign(1000 + 1, vector<int>(1000 + 1, -1000000000));
		dp.assign(1000 + 1, 0);
		dpp[0][1] = 0;
		rep(i, 3, 1000) {
			rep(j, 3, i) {
				rep(k, 1, j - 1) {
					if(j % k) continue;
					dpp[i][j] = max(dpp[i][j], dpp[i - j][k] + 1);
				}
			}			
		}
		rep(i, 1, 1000) {
			rep(j, 1, 1000) dp[i] = max(dp[i], dpp[i][j]);
		}
		return;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
//	solver::init_();
//	solver1::init_();
//	rep(i, 3, 20) if(solver::dp[i] != solver1::dp[i]) 
//		print(i, solver::dp[i], solver1::dp[i]);
	int t; cin >> t; init_();
	rep(tt, 1, t) {
		int n; cin >> n;
		cout << "Case #" << tt << ": " << dp[n] << "\n";
	}
	return 0;
}
