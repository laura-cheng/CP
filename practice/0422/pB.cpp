#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i ,a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	vector<int> a, id;
	void init_(int _n) {
		n = _n;
		a.assign(2 * n + 1, 0);
		id.assign(2 * n + 1, INF);
	}
	int solve() {
		int cur = 0;
		id[n] = 2 * n + 1;
		rrep(i, n + 1, 2 * n) {
			if(a[i] == 1) cur ++;
			else cur --;
			id[cur + n] = min(id[cur + n], i);
		}
		int ans = id[n] - 1; cur = 0;
		rep(i, 1, n) {
			if(a[i] == 1) cur ++;
			else cur --;
			if(id[n - cur] == INF) continue;
			ans = min(ans, id[n - cur] - 1 - i);
		}
		return ans;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, 2 * n) cin >> a[i];
		cout << solve() << "\n";
	}
	return 0;
}

