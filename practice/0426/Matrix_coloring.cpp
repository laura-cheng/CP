#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m;
	vector<vector<bool>> mp;
	vector<int> col[2], vis;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		mp.assign(n + 1, vector<bool>(m + 1, 0));
		col[0].assign(n + m + 1, 0);
		col[1].assign(n + m + 1, 0);
		vis.assign(n + m + 1, 0);
	}
	int solve() {
		rep(i, 1, n) rep(j, 1, m) {
			col[mp[i][j]][i] ++;
			col[mp[i][j]][n + j] ++;
		}
		queue<pii> q; int cnt = 0;
		rep(i, 1, n + m) {
			if(col[0][i] == 0 || col[1][i] == 0) {
				q.push({i, (col[0][i] ? 0 : 1)});
				vis[i] = 1;
			}
		}
		while(q.size()) {
			pii cur = q.front(); q.pop();
			cnt ++;
			int ed = (cur.first <= n ? m : n);
			int id = (cur.first <= n ? n : 0);
			rep(i, 1, ed) if(!vis[id + i]){
				col[cur.second][id + i] -= 1;
				if(col[cur.second][id + i] == 0) {
					q.push({i + id, !cur.second});
					vis[i + id] = 1;
				}
					
			}
		}
		if(cnt != n + m) return -1;
		int ans = 0;
		unordered_map<string, int> a, b;
		rep(i, 1, n) {
			string cur;
			rep(j, 1, m) cur += char('0' + mp[i][j]);
			a[cur] ++;
		}
		rep(i, 1, m) {
			string cur;
			rep(j, 1, n) cur += char('0' + mp[j][i]);
			b[cur] ++;
		}
		for(auto i : a) ans = max(ans, i.second);
		for(auto i : b) ans = max(ans, i.second);
		return n + m - ans;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n, m);
	rep(i ,1, n) rep(j, 1, m) {
		char x; cin >> x;
		mp[i][j] = (x == 'R');
	}
	cout << solve() << "\n";
	return 0;
}
