#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define eps (1e-9)
#define MAXN 1000005
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt199374 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace LL {
	int n;
	vector<int> pre, nxt, a;
	map<int, int> mp;
	void init_(int _n) {
		n = _n;
		pre.assign(n + 2, 0);
		nxt.assign(n + 2, 0);
		mp.clear();
		rep(i, 1, n) {
			pre[i] = i - 1;
			nxt[i] = i + 1;
			mp[a[i] - a[i - 1]] ++;
		}
		nxt[0] = 1;
		mp[a[n + 1] - a[n]] ++;
		return;
	}
	void rid(int x) {
		mp[x] --;
		if(mp[x] == 0) mp.erase(mp.find(x));
	}
	void modify(int x) {
		int aa = pre[x], bb = x, cc = nxt[x];
		rid(a[bb] - a[aa]);
		rid(a[cc] - a[bb]);
		nxt[aa] = cc, pre[cc] = aa;
		mp[a[cc] - a[aa]] ++;
	}
	pii get_cur() {
		if(mp.size() != 3) return {-1, -1};
		else return {mp.begin() -> first, nxt[0]};
	}
};
namespace solver {
	int n, best_a, best_r, best_l;
	vector<int> a;
	void init_(int _n) {
		n = _n;
		a.assign(n + 2, 0);
		a[0] = -INF, a[n + 1] = INF;
		best_a = INF, best_r = INF, best_l = INF;
	}
	void update(int aa, int r, int l) {
		bool upd = 0;
		if(aa < best_a) upd = 1;
		else if(aa == best_a && r < best_r) upd = 1;
		else if(aa == best_a && r == best_r && l < best_l) upd = 1;
		if(upd) {
			best_a = aa;
			best_r = r;
			best_l = l;
		}
	}
	void solve() {
		LL::a = a;
		rep(i, 1, 7) {
			if(__builtin_popcount(i) != 2) continue;
			LL::init_(n);
			int a1 = -1, a2 = -1, pre = -1;
			int r = 0, l = 2;
			rep(j, 0, 2) if((i >> j) & 1) {
				LL::modify(j + 1);
				pre = j + 1;
				if(a1 < 0) a1 = j + 1;
				else a2 = j + 1;
			}
			r = a[a2] - a[a1];
			if(r <= 0) continue;
			pii cur1 = LL::get_cur();
			if(cur1.first > 0) {
				update(a[a1], r, 2);
				update(cur1.second, cur1.first, n - 2);
			}
			rep(j, pre + 1, n) {
				if(a[j] - a[pre] == r) {
					LL::modify(j);
					pii cur = LL::get_cur();
					l ++, pre = j;
					if(cur.first <= 0) continue;
					update(a[a1], r, l);
					update(a[cur.second], cur.first, n - l);
				}
			}
			
		}
		return;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) cin >> a[i];
		solve();
		if(best_a == INF) cout << "-1\n";
		else cout << best_a << " " << best_r << " " << best_l << "\n";
	}
	return 0;
}
