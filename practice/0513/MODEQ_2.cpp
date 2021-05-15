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

#define ll long long int
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
	int cnt[500001];
	ll solve(int n, int m) {
		ll ans = (n > m ? (ll)(n - m) * (ll)(n - m - 1) / 2 : 0) + n - 1;
		rep(i, 0, m) cnt[i] = 0;
		cnt[m] = max(0, n - m);
		rrep(i, 2, min(n, m)) {
			for(int j = m % i; j <= m; j += i) 
				ans += cnt[j];
			cnt[m % i] ++;
		}
		return ans;
	}

};
using namespace solver;
signed main() {
	int t; cin >> t;
	while(t --) {
		int n, m; cin >> n >> m;
		cout << solve(n, m) << "\n";
	}
	return 0;
}
