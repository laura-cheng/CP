#define wiwihorz
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b;i++)
#define all(x) x.begin(), x.end()
using namespace std;
namespace solver {
	const int MAXN = 301;
	int n;
	vector<int> a;
	vector<vector<bool>> mp;
	bitset<MAXN> solve1(bitset<MAXN>, bool);
	bitset<MAXN> solve2(bitset<MAXN>, bool);
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		mp.assign(n + 1, vector<bool>(n + 1, 0));
	}
	void dfs(int x, bitset<MAXN> &node, bool es) {
		node[x] = 0;
		rep(i, 1, n) {
			if(!(mp[i][x] ^ es) || !node[i]) continue;
			dfs(i, node, es);
		}
		return;
	}
	int get(bitset<MAXN> x) {
		int ans = 0;
		rep(i, 1, n) if(x[i]) ans += a[i];
		return ans; 
	}
	bitset<MAXN> solve1(bitset<MAXN> node, bool es) { // find MIS
		if(node.count() == 1) return node;
		int cnt = 0;
		bitset<MAXN> ans;
		rep(i, 1, n) if(node[i]) {
			bitset<MAXN> cur = node;
			cnt ++, dfs(i, node, es);
			if(node.count() == 0 && cnt == 1) {
				return solve2(cur, !es);
			}
			ans = ans | solve1(cur ^ node, es);
		}
		return ans;
	}
	bitset<MAXN> solve2(bitset<MAXN> node, bool es) { // find MC
		if(node.count() == 1) return node;
		int cnt = 0;
		bitset<MAXN>ans;
		rep(i, 1, n) if(node[i]) {
			bitset<MAXN> cur = node;
			cnt ++, dfs(i, node, es);
			if(node.count() == 0 && cnt == 1) {
				return solve1(cur, !es);
			}
			bitset<MAXN> temp = solve2(cur ^ node, es);
			if(get(temp) > get(ans)) ans = temp;
		}
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, m) {
		int aa, bb; cin >> aa >> bb;
		mp[aa][bb] = mp[bb][aa] = 1;
	}
	bitset<MAXN> ans;
	rep(i, 1, n) ans[i] = 1;
	ans = solve2(ans, 0);
	cout << get(ans) << "\n" << ans.count() << "\n";
	int cnt = ans.count();
	rep(i, 1, n) if(ans[i]) cnt --, cout << i << " \n"[cnt == 0];
	return 0;
}

