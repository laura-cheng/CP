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

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	vector<vector<int>> a(m + 1, vector<int>(n + 1, 0));
	vector<int> best;
	rep(i, 1, m) rep(j, 1, n) cin >> a[i][j];
	int ans = -1;
	rep(i, 1, n - 1) {
		vector<pii> b;
		rep(j, 1, m) b.push_back({a[j][i] - a[j][n], j});
		sort(all(b)), reverse(all(b));
		int cnt = 0, cur = 0;
		while(cnt < b.size() && cur + b[cnt].first >= 0) cur += b[cnt++].first;
		if(cnt > ans) {
			best.clear();
			rep(j, cnt, signed(b.size()) - 1) 
				best.push_back(b[j].second);
		}
		ans = max(ans, cnt); 
	}
	cout << m - ans << "\n";
	rep(i, 0, signed(best.size()) - 1) cout << best[i] << " \n"[i + 1 == best.size()];
	return 0;

}