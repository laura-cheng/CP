#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define rrep(i, a, b) for(int i = b; i >= a; --i)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MAXN 1000005
#define MOD 1000000009
#define INF 1000000000000000000
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

int n, m, sz;
vector<int> a, fib, pre;
vector<pii> q;
void build() {
	vector<vector<int>> add(n + 5, vector<int>());
	int pre, cur, nxt, sum = 0;
	cur = pre = nxt = 0;
	for(auto i : q) {
		add[i.first].push_back(1);
		add[i.second + 1].push_back(i.second - i.first + 2);
	}
	rep(i, 1, n) {
		for(auto j : add[i]) {
			if(j == 1) cur = cur + 1;
			else {
				cur = (cur - fib[j]) % MOD;
				pre = (pre - fib[j - 1]) % MOD;
			}
		}
		sum = (sum + cur) % MOD;
		a[i] = (a[i] + sum) % MOD;
		nxt = (pre + cur) % MOD;
		pre = cur, cur = nxt;
	}
	q.clear();
	return;
}
int query(int L, int R) {
	int ans = (a[R] - a[L - 1]) % MOD;
	for(auto i : q) {
		int l, r; tie(l, r) = i;
		int rr = min(R, r) - l + 1, ll = max(0ll, L - l);
		if(rr >= ll) ans = (ans + pre[rr] - pre[ll] + MOD) % MOD;
	}
	return (ans % MOD + MOD) % MOD;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m, sz = 900;
	a.assign(n + 5, 0);
	fib.assign(n + 5, 0);
	pre.assign(n + 5, 0);
	fib[1] = 1, fib[2] = 1;
	rep(i, 3, n) fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
	rep(i, 1, n) pre[i] = (pre[i - 1] + fib[i]) % MOD;
	rep(i, 1, n) cin >> a[i], a[i] = (a[i] + a[i - 1]) % MOD;
	rep(i, 1, m) {
		int t, l, r;
		cin >> t >> l >> r;
		if(t == 1) q.push_back({l, r});
		else cout << query(l, r) << "\n";
		if(q.size() >= sz) build();
	}
	return 0;
}