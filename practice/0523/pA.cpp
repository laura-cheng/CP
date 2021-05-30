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
	const int P = 200000;
	vector<int> cnt;
	vector<vector<int>> move;
	void init_() {
		move.assign(10, vector<int>(P + 1, 0));
		rep(i, 0, 9) {
			cnt.assign(10, 0);
			cnt[i] = 1;
			move[i][0] = 1;
			rep(j, 1, P) {
				int cur = cnt[9];
				rrep(k, 0, 8) cnt[k + 1] += cnt[k], cnt[k] = 0;
				cnt[9] -= cur;
				cnt[0] += cur, cnt[1] += cur;
				rep(k, 0, 9) cnt[k] %= MOD;
				rep(k, 0, 9) move[i][j] += cnt[k];
				move[i][j] %= MOD;
			}
 		}
 		return;
	}
	int solve(int n, int m) {
		int ans = 0;
		while(n) {
			ans = (ans + move[n % 10][m]) % MOD;
			n /= 10;
		}
		return (ans % MOD + MOD) % MOD;
	}
	

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t; init_();
	while(t--) {
		int n, m; cin >> n >> m;
		cout << solve(n, m) << "\n";
	}
	
	return 0;
} 
