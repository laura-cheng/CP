#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
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
namespace solve_ {
	int n, one;
	vector<pii> a;
	vector<int> dp;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
		dp.assign(n, -1);
	}
	int solve() {
		pii cur = a[0];
		sort(all(a)), one = 0;
		int ans = 0;
		dp.assign(n, -1);
		dp[0] = 0;
		int ii = 0, mn = INF;
		rep(i, 0, n - 1) {
			ans += a[i].second;
			if(dp[i] == -1) {
				dp[i] = mn + a[i].first;
			}
			while(ii < n && a[ii].first - a[i].first <= a[i].second) {
				dp[ii] = dp[i], ii ++;
			}
			mn = min(mn, dp[i] - a[i].first - a[i].second);
		}
		ans += dp[n - 1];
		return ans;
	}

};
using namespace solve_;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	for(auto &i : a) cin >> i.first >> i.second;
	cout << solve() << "\n";
	
	return 0;

}
