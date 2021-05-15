#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 10000000000000000000
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
const int P = 1 << 13;
const int MAXN = 13;
struct DP {
	int n, m, a[MAXN][MAXN];
	int dp[2][MAXN][P], all;
	void init_(int _n, int _m) {
		n = _n, m = _m, all = (1 << (m + 1)) - 1;
		memset(dp, 0, sizeof(dp));
		memset(a, 0, sizeof(a));
	}
	void add(int &a, int b) {
		a = (a + b) % MOD;
	}
	bool yes(int x, int id) {
		return (x >> id) & 1;
	}
	int get(int id) {
		return 1 << id; 
	}
	int solve() {
		dp[0][m][0] = 1;
		rep(i, 1, n) {
			int id = (i & 1);
			rep(j, 0, m) rep(k, 0, all) {
				dp[id][j][k] = 0;
			}
			rep(k, 0, (1 << m) - 1) {
				if(!a[i][1] && yes(k, 0)) continue;
				add(dp[id][0][k], dp[!id][m][k]);
			} 
			
			rep(j, 1, m) {
				if(a[i][j]) rep(k, 0, all) {
					if(yes(k, m) == yes(k, j - 1)) {
						if(yes(k, m))add(dp[id][j][k], dp[id][j - 1][~get(m) & ~get(j - 1) & k]);
						if(!yes(k, m)) add(dp[id][j][k], dp[id][j - 1][k | get(m)| get(j - 1)]);
					}
					else {
						add(dp[id][j][k], dp[id][j - 1][~get(j - 1) & k | get(m)]);
						add(dp[id][j][k], dp[id][j - 1][~get(m) & k | get(j - 1)]);
					}
				}
				else rep(k, 0, all) {
					if(yes(k, m) || yes(k, j - 1)) continue;
					add(dp[id][j][k], dp[id][j - 1][k & ~get(j - 1) & ~get(m)]);
				}
			}
		}
		return dp[n & 1][m][0];
	}
} dp;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, m; cin >> n >> m;
		dp.init_(n, m);
		rep(i, 1, n) rep(j, 1, m) {
			cin >> dp.a[i][j];
		}
		cout << "Case " <<tt << ": " << dp.solve() << "\n";
	}
	return 0;
}
