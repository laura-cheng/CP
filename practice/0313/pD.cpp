#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct DP {
	int n, k;
	vector<int> dp, a, pre;
	struct seg {
		int L, R, id;
	};
	void init_(int _n, int _k) {
		n = _n, k = _k;
		dp.assign(n + 1, INF);
		a.assign(n + 1, 0);
		pre.assign(n + 1, 0);
	}
	int f(int i, int j) {
		if(dp[j] == INF || i < j + k) return INF;
		int x = (i + j + 1)/ 2, y = ceil(i + j + 1, 2);
		int v = (a[x] + a[y]) / 2;
		return dp[j] + v * (2 * x - j - i) + pre[i] + pre[j] - 2 * pre[x];
	}
	int bs(int i, int j, int L, int R) {
		// find first spot i is better than j
		int l = L, r = R + 1;
		while(r - l > 1) {
			int mid = (l + r) / 2;
			if(f(mid, i) < f(mid, j)) r = mid;
			else l = mid;
		}
		return r;
	}
	int solve() {
		vector<seg> dq(n + 10, {0, 0, 0});
		sort(all(a));
		rep(i, 1, n) pre[i] = pre[i - 1] + a[i];
		int l = 1, r = 1;
		dp[0] = 0; dq[l] = {0, n, 0};
		rep(i, k, n) {
			while(dq[l].R < i) l++;
			dp[i] = f(i, dq[l].id);
			while(l <= r && f(dq[r].L, dq[r].id) 
				> f(dq[r].L, i - k + 1)) r--;
			if(l > r) dq[++r] = {i, n, i - k + 1};
			else { 
				int ii = bs(i - k + 1, dq[r].id, dq[r].L, n);
				if(ii <= n) dq[r].R = ii - 1, dq[++r] = {ii, n, i - k + 1};
			} 
		}
		return dp[n];
	}

} dp;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	dp.init_(n, k);
	rep(i, 1, n) cin >> dp.a[i];
	cout << dp.solve() << "\n";
	
	return 0;
}
