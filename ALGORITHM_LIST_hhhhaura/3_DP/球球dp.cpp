#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000000000000
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) out("[" + string(#a) +"] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void out() {cerr << endl;}
template<class T1, class ... T2> void out(T1 a, T2 ... e) {cerr << a <<" ", out(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, k;
char c;
vector<int> a, fac, inv;
void add(int &a, int b) {
	a = (a + b) % MOD;
}
int solve1() {
	int s = n;
	rep(i, 1, k) s -= a[i];
	vector<int> dp(s + 1, 0);
	dp[0] = 1;
	rep(i, 1, s) rep(j, i, s) {
		add(dp[j], dp[j - i]);
	}
	return dp[s];
}
int pow_(int a, int times) {
	int ans = 1;
	for(;times > 0; times >>= 1, a = a * a % MOD) {
		if(times & 1) ans = ans * a % MOD;
	}
	return ans;
}
void build() {
	fac.assign(n + 1, 1);
	inv.assign(n + 1, 1);
	rep(i, 1, n) fac[i] = fac[i - 1] * i % MOD;
	inv[n] = pow_(fac[n], MOD - 2);
	rrep(i, 0, n - 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
	return;
}
int solve2() {
	n = n - k, build();
	vector<vector<int>> f(n + 1, vector<int>(n + 1, 0));
	f[0][0] = 1;
	rep(i, 1, n) rep(j, 1, n) {
		add(f[i][j], i * f[i][j - 1]);
		add(f[i][j], f[i - 1][j - 1]);
	}
	rep(i, 1, n) rep(j, 1, n) {
		add(f[i][j], f[i - 1][j]);
	}
	int ans = 0;
	rep(i, 0, n) {
		int C = fac[n] * inv[i] % MOD * inv[n - i] % MOD;
		int K = pow_(k, n - i);
		int ff = f[i][i];
		int cur = C * K % MOD * ff % MOD;
		add(ans, cur);
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> c >> n >> k;
	a.assign(n + 1, 0);
	rep(i, 1, k) {
		cin >> a[i];
	}
	if(c == 'U') cout << solve1() << "\n";
	else cout << solve2() << "\n";
	return 0;
}  
