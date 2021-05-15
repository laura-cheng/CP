#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)
#define MOD 1000000007

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
struct segment_tree {
	int n;
	vector<int> seg, a;
	void init_(int _n, vector<int> _a) {
		n = _n, a = _a;
		seg.assign(2 * n + 1, 0);
		build(1, n);
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) seg[nd] = a[L];
		else {
			build(L, mid);
			build(mid + 1, R);
			pull(L, R);
		}
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		seg[nd] = __gcd(seg[lch], seg[rch]);
	}
	int query(int L, int R, int l, int r) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return 0;
		else if(l <= L && r >= R) return seg[nd];
		else return __gcd(
				query(L, mid, l, r),
				query(mid + 1, R, l, r)
		);
	}
	int ask(int L, int R) {
		return query(1, n, L, R);
	}
};
namespace SOLVE {
	int n;
	vector<int> a, pre, dp;
	segment_tree st;
	void init_(int _n) {
		n = _n;
		a.assign(n + 2, 0);
		pre.assign(n + 2, 0);
		dp.assign(n + 2, 0);
	}
	void build() { // pre, 
		st.init_(n, a);
		int l = 1;
		rep(i, 1, n) {
			while(st.ask(l, i) == 1) l ++;
			pre[i] = l;
		}
		return;
	}
	int pow_(int a, int times) {
		int ans = 1;
		for(;times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	void DP() {
		dp.assign(n + 2, 0);
		vector<int> sum(n + 2, 0);
		dp[0] = 1;
		rep(i, 1, n) {
			int l = (pre[i] == 1 && (__gcd(a[1], st.ask(1, i)) != 1)) ? 1 : max(2ll, pre[i]);
			sum[i] = (sum[i - 1] + dp[i - 1]) % MOD;
			dp[i] = (sum[i] - sum[l - 1]) % MOD;
		}
	}
	int solve() {
		if(st.ask(1, n) != 1) return (pow_(2, n) - n + MOD) % MOD;
		int cur = a[1], ans = 0;
		DP();
		rrep(i, 2, n + 1) {
			if(cur != __gcd(cur, a[i])) {
				cur = __gcd(cur, a[i]);
				a[1] = cur, DP();
			}
			else cur = __gcd(cur, a[i]);
			if(cur == 1) break;
			ans = (ans + dp[i - 1]) % MOD;
		}
		return (ans % MOD + MOD) % MOD;
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	build();
	cout << solve() << "\n";
	
	return 0;
}
