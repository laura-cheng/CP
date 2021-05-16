#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int,int>
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
#define a first
#define b second
int n, A, B, C;
vector<int> dp, pre;
bool check(pii i, pii j, pii k) {
	int aa = j.b - i.b, bb = i.a - j.a;
	int cc = k.b - i.b, dd = i.a - k.a;
	return aa * dd >= bb * cc;
}
int val(int x, pii i) {
	return i.a * x + i.b;
}
int solve() {
	vector<pii> q(n + 1, {0, 0});
	int l = 0, r = 0;
	q[0] = {0, 0};
	rep(i, 1, n) {
		while(l + 1 <= r && val(pre[i], q[l]) 
			<= val(pre[i], q[l + 1])) l ++;
		dp[i] = (
			val(pre[i], q[l]) + 
			pre[i] * pre[i] * A +
			pre[i] * B + C
		);
		pii cur = {
			-2 * A * pre[i], 
			dp[i] + A * pre[i] * pre[i] -
			B * pre[i] 
		};
		while(l < r && check(q[r - 1], q[r], cur)) r--;
		q[++r] = cur;
	}
	return dp[n];
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> A >> B >> C;
	pre.assign(n + 1, 0);
	dp.assign(n + 1, 0);
	rep(i, 1, n) {
		cin >> pre[i];
		pre[i] += pre[i - 1];
	}
	cout << solve() << "\n";
	return 0;
}
