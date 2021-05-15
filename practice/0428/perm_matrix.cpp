#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
using namespace std;
namespace solver {
	int n, m;
	vector<vector<int>> a, ans;
	vector<int> nxt, rt;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(n, vector<int>(m, 0));
		ans.assign(n, vector<int>(m, 0));
		nxt.assign(m * n, -1);
		rt.assign(m, 0);
	} 
	bool solve() {
		rep(i, 0, n - 1) {
			sort(all(a[i]));
			if(i & 1) reverse(all(a[i]));
		}
		rep(i, 0, m - 1) rt[i] = (n - 1) * m + i;
		rrep(i, 0, n - 2) {
			int l = 0, r = m - 1;
			rep(j, 0, m - 1) {
				if(a[i][j] == a[i + 1][j]) {
					if(l < m && a[i + 1][l] != a[i][j] 
						&& a[i][l] != a[i][j]) swap(rt[l], rt[j]), l ++;
					else if(r >= 0 && a[i + 1][r] != a[i][j] 
						&& a[i][r] != a[i][j]) swap(rt[r], rt[j]), r --;
					else return 0;
				}
			}
			rep(j, 0, m - 1) {
				nxt[i * m + j] = rt[j];
				rt[j] = i * m + j;
			}
		}
		rep(j, 0, m - 1) {
			for(int i = 0, nd = rt[j]; i < n; i++, nd = nxt[nd]) {
				ans[i][j] = a[nd / m][nd % m];
			}
		}
		return true;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i, 0, n - 1) rep(j, 0, m - 1) cin >> a[i][j];
	if(!solve()) cout << "-1\n";
	else rep(i, 0, n - 1) rep(j, 0, m - 1) cout << ans[i][j] << " \n"[j + 1 == m];
	return 0;
}
