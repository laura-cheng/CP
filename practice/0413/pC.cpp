#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
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
	vector<int> pre, dp;
	void init_() {
		int n = 2e6;
		pre.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		dp[1] = 1;
		rep(i, 2, n) {
			dp[i] = (dp[i - 1] + 2 * dp[i - 2]) % MOD;
			pre[i] = (pre[max(0ll, i - 3)] + dp[i - 2] * 4) % MOD;
		}
		return;
	}
	int query(int x) {
		return pre[x];
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	init_();
	while(t --) {
		int x; cin >> x;
		cout << query(x) << "\n";
	}	
	return 0;
}
