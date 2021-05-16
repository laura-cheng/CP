#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1e13
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
#define m first
#define k second
int n, k;
vector<int> p, q, dp[2], q1;
vector<pii> a, a1;
int val(pii p, int x) {
	return p.m * x + p.k;
}
bool check(pii a, pii b, pii c) {
	return (a.k - c.k) * (b.m - a.m) 
		> (a.k - b.k) * (c.m - a.m);
}
bool cmp(int x, int y) {
	return p[x] < p[y];
}	
void CDQ(int L, int R, bool t) {
	if(L == R) return;
	else {
		int mid = (L + R) / 2;
		CDQ(L, mid, t), CDQ(mid + 1, R, t);
		vector<pii> cur(R - L + 1, {0, 0});
		int l = 0, r = -1;
		rep(i, L, mid) {
			while(l < r && 
				!check(cur[r - 1], cur[r], a[i])) r--;
			cur[++r] = a[i];
		}
		rep(i, mid + 1, R) {
			int x = q[i];
			while(l < r && val(cur[l], p[x]) 
				<= val(cur[l + 1], p[x])) l++;
			dp[t][x] = max(
				dp[t][x], 
				val(cur[l], p[x]) + p[x] * p[x]
			);
		}
		a1.assign(R - L + 1, {0, 0});
		q1.assign(R - L + 1, 0);
		merge(
			a.begin() + L, a.begin() + mid + 1,
			a.begin() + mid + 1, a.begin() + R + 1,
			a1.begin()
		);
		merge(
			q.begin() + L, q.begin() + mid + 1,
			q.begin() + mid + 1, q.begin() + R + 1,
			q1.begin(), cmp
		);
		rep(i, L, R) a[i] = a1[i - L];
		rep(i, L, R) q[i] = q1[i - L];
	}
	return;
}
int solve() {
	dp[0].assign(n + 1, 0);
	dp[1].assign(n + 1, -INF);
	dp[0][0] = 0;
	rep(i, 1, k) {
		int id = (i & 1);
		a.clear(), q.clear();
		dp[id].assign(n + 1, -INF);
		rep(j, 1, n) q.push_back(j);
		rep(j, 1, n) {
			a.push_back({-2 * p[j], 
				dp[!id][j - 1] + p[j] * p[j]});
		}
		CDQ(0, signed(q.size()) - 1, i & 1);
		rep(j, 1, n) dp[id][j] = max(dp[id][j - 1], dp[id][j]);
	}
	return dp[k & 1][n];
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> k;
	p.assign(n + 1, 0);
	rep(i, 1, n) cin >> p[i];
	cout << solve() << "\n";
	return 0;
}