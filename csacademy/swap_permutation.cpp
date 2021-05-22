#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
using namespace std;
#define pii pair<int, int>
namespace solver {
	int n, m, k;
	vector<int> a, b;
	vector<pii> p, c;
	void init_(int _n, int _m, int _k) {
		n =_n, m = _m, k = _k;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		c.assign(m + 1, {0, 0});
		p.assign(m + 1, {0, 0});
	}
	int solve() {
		rep(i, 1, m) {
			int aa = p[i].first, bb = p[i].second;
			c[i] = {a[aa], a[bb]};	
			swap(a[aa], a[bb]);		
		}
		rep(i, 1, n) b[a[i]] = i;
		rep(i, 1, m) {
			int aa = c[i].first, bb = c[i].second;
			swap(a[b[aa]], a[b[bb]]);
			if(a[k] == 1) return i;
			swap(a[b[aa]], a[b[bb]]);
		}
		return 0;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, k; 
	cin >> n >> m >> k;
	init_(n, m, k);
	rep(i, 1, n) a[i] = i;
	rep(i, 1, m) cin >> p[i].first >> p[i].second;
	cout << solve() << "\n";
	return 0;
}
