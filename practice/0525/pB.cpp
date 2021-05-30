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
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int R, G, B;
	const int P = 201;
	int dp[P][P][P];
	vector<int> r, g, b;
	void init_(int _R, int _G, int _B) {
		R = _R, G = _G, B = _B;
		r.assign(R + 1, 0);
		g.assign(G + 1, 0);
		b.assign(B + 1, 0);
	}
	void update(int &a, int b) {
		a = max(a, b);
	}
	int solve() {
		sort(all(r)), sort(all(g)), sort(all(b));
		rep(i, 0, R) rep(j, 0, G) rep(k, 0, B) {
			if(i && j && j && k) update(dp[i][j][k], dp[i - 1][j - 1][k - 1]);
			if(i) update(dp[i][j][k], dp[i - 1][j][k]);
			if(j) update(dp[i][j][k], dp[i][j - 1][k]);
			if(k) update(dp[i][j][k], dp[i][j][k - 1]);
			
			if(i && j) update(dp[i][j][k], dp[i - 1][j - 1][k] + r[i] * g[j]);
			if(i && k) update(dp[i][j][k], dp[i - 1][j][k - 1] + r[i] * b[k]);
			if(j && k) update(dp[i][j][k], dp[i][j - 1][k - 1] + g[j] * b[k]);
		}
		return dp[R][G][B]; 
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int R, G, B; cin >> R >> G >> B;
	init_(R, G, B);
	rep(i, 1, R) cin >> r[i];
	rep(i, 1, G) cin >> g[i];
	rep(i, 1, B) cin >> b[i];
	cout << solve() << "\n";
	return 0;
}
