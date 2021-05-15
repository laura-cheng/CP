#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) for(int i = a; i <= b; i++)

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a )
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int m, n;
	vector<vector<int>> dp, a;
	void init_(int _m, int _n) {
		m = _m, n = _n;
		dp.assign(m + n + 1, vector<int>(m + n + 1, INF));
		a.assign(m + n + 1, vector<int>(m + n + 1, 0));
	}
	void build() {
		rep(i, 1, m + n) rep(j, 1, m + n) {
			if(a[i][j]) dp[i][j] = 1;
		}	
		rep(k, 1, m) rep(i, 1, n + m) rep(j, 1, m + n) {
			dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
		}
		return;
	}
	int query(int a, int b) {
		int x = dp[a][b], cnt = 0;
		if(x == INF) return -1;
		else {
			while(x > 1) {
				cnt ++;
				x = x - (x + 1) / 3;
			}
			return cnt;
		}	
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int m, n, p; 
		cin >> m >> n >> p;
		init_(m, n);
		rep(i, 1, n + m) rep(j, 1, m + n) {
			char x; cin >> x;
			a[i][j] = bool(x == 'Y');
		}
		build();
		cout << "Case #" << tt << ": ";
		rep(i ,1, p) {
			int x, y; cin >> x >> y;
			cout << query(x, y) << " \n"[i == p];
		}
	}	
	return 0;
}
