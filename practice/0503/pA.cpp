#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b;i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, k;
	vector<int> a;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, 0);
	}
	int solve() {
		int ans = 0;
		vector<int> temp;
		sort(all(a));
		temp.push_back(a[1] - 1);
		temp.push_back(k - a[n]);
		rep(i, 2, n) {
			int cur = a[i] - a[i - 1] - 1;
			ans = max(cur, ans);
			temp.push_back(ceil(cur, 2));
		}
		sort(all(temp)), reverse(all(temp));
		ans = max(ans, temp[0] + temp[1]);
		return ans;
		
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, k; cin >> n >> k;
		init_(n, k);
		rep(i, 1, n) cin >> a[i];
		cout << "Case #" << tt << ": " << (lld)solve() / (lld)k << "\n";
	}
	return 0;
}

