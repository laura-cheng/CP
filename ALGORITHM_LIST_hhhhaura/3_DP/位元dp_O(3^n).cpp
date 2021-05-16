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

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
const int p = 16;
int n, m;
int a[p][p], cnt[p][1 << p];
int dp[1 << p][p], cur[1 << p];
void build() {
	rep(i, 0, n - 1) {
		rep(j, 0, (1 << n) - 1) if(!((j >> i) & 1)) {
			rep(k, 0, n - 1) if((j >> k) & 1) {
				cnt[i][j] += a[i][k];
			}
		}
	}
	return;
}
int cal(int a, int b) {
	int ans = 0;
	rep(i, 0, n - 1) if((a >> i) & 1) {
		ans += cnt[i][b];
	}
	return ans;
}
int solve() {
	rep(i, 0, n - 1) rep(j, 0, (1 << n) - 1) {
		dp[j][i] = INF;
	}
	dp[1][0] = 0;
	rep(i, 0, (1 << n) - 1) {
		rep(j, 0, n - 1) if((i >> j) & 1) {
			int mask = i ^ (1 << j);
			rep(k, 0, n - 1) if(((mask >> k) & 1) && a[k][j]) {
				dp[i][j] = min(dp[i][j], dp[mask][k] + cnt[j][mask ^ (1 << k)]);
			}
			for(int k = i; k > 0; k = (k - 1) & i) if((k >> j) & 1){
				dp[i][j] = min(dp[i][j] , dp[k][j] + cal(k ^ (1 << j), i ^ k));
		}
	}
	return dp[(1 << n) - 1][n - 1];
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m) {
		int x, y, z;
		cin >> x >> y >> z;
		x--, y--;
		a[x][y] = a[y][x] = z;
	}
	build();
	cout << solve() << "\n";
	return 0;
}