#define hhhhaura
#include <bits/stdc++.h>
#pragma GC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()  
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 15
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef hhhhaura
#define print(a...) out("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << "\n"[next(L) == R], ++L;}
void out() {cerr << endl;}
template<class T1, class... T2> void out(T1 a, T2 ... e) {cerr << a << " ", out(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
int t, n, m, a[MAXN][MAXN];
int dp[MAXN][MAXN][(1 << 13)];
void add(int &a, int b) {
	a = (a + b) % MOD;
}
int solve() {
	memset(dp, 0, sizeof(dp));
	dp[0][m][0] =  1;
	rep(i, 1, n) {
		rep(k, 0, (1 << m) - 1) {
			dp[i][0][k<<1] = dp[i - 1][m][k];
		}
		rep(j, 1, m) {
			int x = (1 << j), y = (1 << (j - 1));
			rep(k, 0, (1 << (m + 1)) - 1) {
				if(a[i][j]) {
					dp[i][j][k] = dp[i][j - 1][k ^ x ^ y];
					if(bool(x & k) != bool(y & k)) {
						add(dp[i][j][k], dp[i][j - 1][k]);
					}
				}
				else {
					if((k & x) || (k & y)) dp[i][j][k] = 0;
					else add(dp[i][j][k], dp[i][j - 1][k]);
				}
				
			}
		}
	}
	return dp[n][m][0];
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> t;
	rep(tt, 1, t) {
		cin >> n >> m;
		rep(i, 1, n) rep(j, 1, m) {
			cin >> a[i][j];
		}
		cout << "Case " << tt << ": " << solve() << "\n";
	}
	return 0;
}
