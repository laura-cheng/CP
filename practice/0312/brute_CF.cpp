#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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

struct DP {
	int n, k;
	vector<lld> t, pre, rev, sum, dp[2];
	struct ln {
		lld m, k;
	};
	void init_(int _n, int _k) {
		n = _n, k = _k;
		dp[0].assign(n + 1, -INF);
		dp[1].assign(n + 1, -INF);
		t.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		rev.assign(n + 1, 0);
		sum.assign(n + 1, 0);
	}
	void build() {
		rep(i, 1, n) {
			lld x = 1.0 / (lld) t[i];
			pre[i] = pre[i - 1] + t[i];
			rev[i] = rev[i - 1] + x;
			sum[i] = sum[i - 1] + x * pre[i];
		}
	}
	lld val(ln a, lld x) {
		return a.m * x + a.k;
	}
	bool check(ln a, ln b, ln c) {
		return (a.k - b.k) * (c.m - b.m) <
			(b.k - c.k) * (b.m - a.m);
	}
	lld solve() {
		vector<ln> dq(n + 5, {0, 0});
		int l = 1, r = 0;
		rep(i, 1, k) {
			int id = i & 1;
			l = 1, r = 1;
			dq[1] = {0, 0};
			rep(j, 1, n) {
				while(l < r && val(dq[l], rev[j]) 
					<= val(dq[l + 1], rev[j])) l ++;
				dp[id][j] = val(dq[l], rev[j]) - sum[j];
				ln cur = {pre[j], dp[!id][j] + sum[j] - pre[j] * rev[j]};
				while(l < r && !check(dq[r - 1], dq[r], cur)) r--;
				dq[++r] = cur;
			}
		}
		return -dp[k & 1][n];
	}
} dp;
struct aliens {

	struct ln {
		lld m, k; int id;
	};
	struct res {
		lld v; int t;
	};
	int n, k;
	vector<lld> t, pre, rev, sum, dp;
	vector<ln> dq;
	vector<int> cnt;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		dp.assign(n + 1, -INF);
		t.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		rev.assign(n + 1, 0);
		sum.assign(n + 1, 0);
	}
	void build() {
		rep(i, 1, n) {
			lld x = 1.0 / (lld) t[i];
			pre[i] = pre[i - 1] + t[i];
			rev[i] = rev[i - 1] + x;
			sum[i] = sum[i - 1] + x * pre[i];
		}
	}
	lld val(ln a, lld x) {
		return a.m * x + a.k;
	}
	bool check(ln a, ln b, ln c) {
		return (a.k - b.k) * (c.m - b.m) <
			(b.k - c.k) * (b.m - a.m);
	}
	res vval(lld x) {
		dq.assign(n + 5, {0, 0, 0});
		cnt.assign(n + 1, 0);
		int l = 1, r = 0;
		dq[1] = {0, 0, 0};
		rep(i, 1, n) {
			while(l < r && val(dq[l], rev[i]) 
				<= val(dq[l + 1], rev[i])) l ++;
			dp[i] = val(dq[l], rev[i]) - sum[i] - x;
			cnt[i] = cnt[dq[l].id] + 1;
			ln cur = {pre[i], dp[i] + sum[i] - pre[i] * rev[i], i};
			while(l < r && !check(dq[r - 1], dq[r], cur)) r--;
			dq[++r] = cur;
		}
		return {dp[n], cnt[n]};
	}
	lld solve() {
		lld l = 0, r = 1e15;
		rep(i, 1, 150) {
			lld mid = (l + r) / 2;
			res cur = vval(mid);
			if(cur.t >= k) l = mid;
			else r = mid;
		}
		res ans = vval(l);
		return -(ans.v + l * k);
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	dp.init_(n, k);
	rep(i, 1, n) cin >> dp.t[i];
	dp.build();
	cout << fixed << setprecision(6) << dp.solve() << "\n";
	return 0;
}
