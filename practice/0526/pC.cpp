#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define INF 1000000000000000000
using namespace std;
namespace solver {
	int n; 
	vector<int> a, b, nxt;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		b.assign(n + 1, n + 1);
		nxt.assign(n + 1, INF);
	}
	int solve() {
		rrep(i, 1, n) {
			nxt[i] = b[a[i]];
			b[a[i]] = i;
		}
		int ans = 0, x = 0, y = 0;
		rep(i, 1, n) {
			if(a[i] == a[x]) x = i;
			else if(a[i] == a[y]) y = i;
			else if(nxt[x] > nxt[y]) ans ++, x = i;
			else ans ++, y = i;
		}
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);	
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	return 0;
}
