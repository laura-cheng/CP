#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define eps (1e-9)
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

//#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	vector<vector<int>> mp;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
	}
	void solve() {
		pii p = {0, 0};
		bool suc = 0;
		rep(i, 1, n) {
			mp[i].push_back(i);
			sort(all(mp[i]));
			int cur = 1;
			for(auto j : mp[i]) if(cur == j) cur = j + 1;
			if(cur <= n) {
				p = {i, cur};
				suc = 1;
				break;
			}
			if(suc) break;
		}
		if(p.first == 0) cout << "NO\n";
		else {
			cout << "YES\n";
			if(p.first > p.second) swap(p.first, p.second);
			vector<int> a(n + 1, 0);
			a[p.first] = n, a[p.second] = n - 1;
			int cur = n - 2;
			rep(i, 1, n) if(!a[i]) a[i] = cur, cur --;
			rep(i, 1, n) cout << a[i] << " \n"[i == n];
			rep(i, 1, n) {
				if(i == p.second) cout << a[p.first] << " \n"[i == n];
				else cout << a[i] << " \n"[i == n]; 
			} 
			
		}
		return;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, m ) {
		int a, b; cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	solve();
	return 0;
} 	
