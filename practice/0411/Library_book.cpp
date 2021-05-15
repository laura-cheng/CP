#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m;
	vector<int> an, bn, am, bm;
	vector<vector<int>> mx1, mx2, dp[2];
	vector<pii> pro, stu;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		an.assign(n + 1, 0);
		bn.assign(n + 1, 0);
		dp[0].assign(n + 1, vector<int>(m + 1, INF));
		dp[1].assign(n + 1, vector<int>(m + 1, INF));
	}
	void build() {
		sort(all(pro)), sort(all(stu));
		rep(i, 0, n - 1) an[i + 1] = pro[i].first, bn[i + 1] = pro[i].second;
		int cur = 0;
		bm.push_back(stu[m - 1].second);
		am.push_back(stu[m - 1].first);
		rrep(i, 0, m - 2) {
			if(stu[i].second <= bm.back()) continue;
			bm.push_back(stu[i].second);
			am.push_back(stu[i].first);
		}
		am.push_back(0);
		bm.push_back(0);
		reverse(all(am));
		reverse(all(bm));
		m = am.size() - 1;
		return;
	}
	int solve() {
		dp[0][0][0] = 0;
		dp[1][0][0] = 0;
		rep(i, 1, n) dp[0][i][0] = max(dp[0][i - 1][0], an[i]) + bn[i];
		rep(j, 1, m) dp[1][0][j] = max(dp[1][0][j - 1], am[j] + bm[j]);
		rep(i, 1, n) rep(j, 1, m) {
			dp[0][i][j] = min(dp[0][i][j], max(an[i], min(dp[0][i - 1][j], dp[1][i - 1][j])) + bn[i]);
			dp[1][i][j] = min(max(dp[1][i][j - 1], am[j] + bm[j]), max(dp[0][i][j - 1], am[j]) + bm[j]);
		}
		return min(dp[0][n][m], dp[1][n][m]);
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 1, n) {
		int a, b; cin >> a >> b;
		pro.push_back({a, b});
	}
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		stu.push_back({a, b});
	}
	build();
	cout << solve() << "\n";
	return 0;
}
