#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define all(x) x.begin(), x.end()
using namespace std;
namespace bit {
	int n;
	vector<int> val;
	inline int lowbit(int x) {return x & (-x);}
	void init_(int _n) { n = _n, val.assign(n + 1, 0);}
	void modify(int x, int v) {
		for(int i = x; i <= n; i += lowbit(i)) {
			val[i] += v;
		}
	}
	int query(int x) {
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i)) {
			ans += val[i];
		}
		return ans;
	}
	int ask(int L, int R) {return query(R) - query(L - 1);}
};
namespace solver {
	int n;
	vector<vector<int>> row, col;
	vector<int> x, y, vx, vy, cnt;
	struct query {
		int x, tp, L, R, id;  
		bool operator<(query b) {
			if(x != b.x) return x < b.x;
			else return tp < b.tp;
		}
	};
	vector<query> qq;
	void init_(int _n) {
		n = _n;
		row.assign(n + 1, vector<int>());
		col.assign(n + 1, vector<int>());
		x.assign(n + 1, 0);
		y.assign(n + 1, 0);
		cnt.assign(n + 1, 0);
		vx.clear();
		vy.clear();
		qq.clear();
		bit::init_(n);
	}
	bool solve() {
		rep(i, 1, n) {
			vx.push_back(x[i]);
			vy.push_back(y[i]);
		}
		sort(all(vx)), vx.resize(unique(all(vx)) - vx.begin());
		sort(all(vy)), vy.resize(unique(all(vy)) - vy.begin());
		rep(i, 1, n) {
			x[i] = lower_bound(vx.begin(), vx.end(), x[i]) - vx.begin() + 1;
			y[i] = lower_bound(vy.begin(), vy.end(), y[i]) - vy.begin() + 1;
			row[y[i]].push_back(x[i]);
			col[x[i]].push_back(y[i]);
		}
		rep(i, 1, n) {
			row[i].push_back(0);
			row[i].push_back(n + 1);
			col[i].push_back(0);
			col[i].push_back(n + 1);
			sort(all(row[i]));
			sort(all(col[i]));
		}
		rep(i, 1, n) {
			int r = lower_bound(row[y[i]].begin(), row[y[i]].end(), x[i]) - row[y[i]].begin();
			int c = lower_bound(col[x[i]].begin(), col[x[i]].end(), y[i]) - col[x[i]].begin();
			int u = col[x[i]][c - 1], d = col[x[i]][c + 1];
			int L = row[y[i]][r - 1], R = row[y[i]][r + 1];
			qq.push_back({L, 1, u, d, i});
			qq.push_back({R - 1, 2, u, d, i});
			qq.push_back({x[i], 0, y[i], 0, 0});
		}
		sort(all(qq));
		for(auto i : qq) {
			if(i.tp == 0) bit::modify(i.L, 1);	
			else if(i.tp == 1) cnt[i.id] -= bit::ask(i.L + 1, i.R - 1);
			else cnt[i.id] += bit::ask(i.L + 1, i.R - 1);
		}
		bool ans = 1;
		rep(i, 1, n) ans &= (cnt[i] == 1);
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) cin >> x[i] >> y[i];
		cout << solve() << "\n";
	}
	return 0;
}
