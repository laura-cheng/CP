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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct pt {
	int len, pos, id;
	bool operator>(pt b) {
		if(len != b.len) return len > b.len;
		if(id != b.id) return id > b.id; 
	}
};
struct BIT {
	int n;
	vector<pt> v;
	void init_(int _n) {
		n = _n;
		v.assign(n + 1, {0, 0, 0});
	}
	int lowbit(int x) {
		return (x & -x);
	}
	void modify(int x, pt cur) {
		for(int i = x; i <= n; i += lowbit(i)) {
			if(cur > v[i]) v[i] = cur;
		}
		return;
	}
	pt query(int x) {
		pt ans = {0, 0, 0};
		for(int i = x; i > 0; i -= lowbit(i)) {
			if(v[i] > ans) ans = v[i];
		}
		return ans;
	}
};
namespace DP {
	vector<int> a, b, v, pos, ans, pre, dp, val;
	int n; BIT bit;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		pos.assign(n + 1, 0);
		v.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		dp.assign(n + 1, 0);
		val.clear();
		bit.init_(n);
	}
	void solve() {
		rep(i, 1, n) val.push_back(a[i]);
		sort(all(val));
		rep(i, 1, n) {
			a[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
			b[i] = lower_bound(val.begin(), val.end(), b[i]) - val.begin() + 1;
		}
		rep(i, 1, n) pos[b[i]] = i;
		rep(i, 1, n) v[i] = pos[a[i]];
//		vprint(all(v));
		rrep(i, 1, n) {
			pt cur = bit.query(n - v[i]);
			pre[i] = cur.pos, dp[i] = cur.len + 1;
			bit.modify(n - v[i] + 1, {cur.len + 1, i, a[i]});
		}
		int len = 0, p = 0;
		rep(i, 1, n) len = max(len, dp[i]);
		rep(i, 1, n) if(dp[i] == len) {
			if(a[i] > a[p]) p = i;	
		}
		rep(i, 1, len) {
			cout << val[a[p] - 1] << " \n"[i == len];
			p = pre[p];
		}
	}
};
using namespace DP;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	solve();

	return 0;
}
