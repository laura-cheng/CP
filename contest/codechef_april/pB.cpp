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
int n, m, k;
vector<vector<int>> a, pre;
int bs(int x, int y) {
	int l = max(0ll, x - y), r = x + 1;
	while(r - l > 1) {
		int mid = (l + r) / 2;
		int x1 = mid, y1 = y - (x - x1);
		if(pre[x][y] - pre[x1 - 1][y] - 
			pre[x][y1 - 1] + pre[x1 - 1][y1 - 1] >= 0) {
			r = mid;	
		}
		else l = mid;
	}
	return x - r + 1;
}
void init_(int _n, int _m, int _k) {
	n = _n, m = _m, k = _k;
	a.assign(n + 1, vector<int>(m + 1, 0));
	pre.assign(n + 1, vector<int>(m + 1, 0));
}
int solve() {
	int ans = 0;
	rep(i, 1, n) rep(j, 1, m) {
		a[i][j] -= k;
		pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i][j];
	}	
	rep(i, 1, n) rep(j, 1, m) ans += bs(i, j);
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n, m, k;
		cin >> n >> m >> k;
		init_(n, m, k);
		rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
		cout << solve() << "\n";
	}
	
	return 0;

}
