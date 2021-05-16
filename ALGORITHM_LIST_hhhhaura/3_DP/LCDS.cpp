#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n;
vector<int> a, b, ans;
vector<vector<int>> dp, pre;
void backtrack(int i, int j) {
	if(i == 0) return;
	if(pre[i][j] == -1) backtrack(i - 1, j);
	else backtrack(i - 1, pre[i][j]), assert(j != 0), ans.push_back(b[j]);
}
void solve() {
	dp.assign(n + 1, vector<int>(n + 1, 0));
	pre.assign(n + 1, vector<int>(n + 1, -1));
	b[0] = INF; int mx = 0;
	rep(i, 1, n) {
		mx = 0;
		rep(j, 1, n) {
			if(a[i] < b[j] && 
				dp[i - 1][mx] < dp[i - 1][j]) mx = j;
			dp[i][j] = dp[i - 1][j];
			if(a[i] == b[j]) {
				dp[i][j] = dp[i - 1][mx] + 1;
				pre[i][j] = mx;
			}
		} 
	}
	int ans = 0;
	rep(i, 0, n) {
		if(dp[n][ans] < dp[n][i]) ans = i;
	}
	backtrack(n, ans);
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		cin >> n;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		ans.clear();
		rep(i, 1, n) cin >> a[i];
		rep(i, 1, n) cin >> b[i];
		solve();
		rep(i, 0, signed(ans.size()) - 1) {
			cout << ans[i] << " \n"[i + 1 == ans.size()];
		}
		if(ans.size() == 0) cout << "\n";
	}
	return 0;
}
