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
	int r, c;
	vector<vector<int>> mp, mp1;
	void init_(int _r, int _c) {
		r = _r, c = _c;
		mp.assign(r + 1, vector<int>(c + 1, 0));
		mp1.assign(r + 1, vector<int>(c + 1, 0));
	}
	int solve() {
		int ans = 0;
		rep(i, 1, r) rep(j, 1, c) {
			if(mp[i][j] == mp1[i][j]) continue;
			if(i < r && mp[i + 1][j] != mp1[i + 1][j]) {
				ans ++;
				d
			}
		}
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);

	return 0;
}
