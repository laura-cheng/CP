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
#define MOD 1000000007
#define eps (1e-9)

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
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, m;
	vector<vector<char>> a;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(n + 1, vector<char>(n + 1, ' '));
	}
	void solve() {
		int x = 0, y = 0, z = 0;
		rep(i, 1, n) rep(j, 1, n) if(i != j){
			if(a[i][j] == a[j][i]) x = i, y = j;
		}
		if(x && y) {
			cout << "YES\n";
			rep(i, 1, m + 1) {
				if(i & 1) cout << x << " \n"[m + 1 == i];
				else cout << y << " \n"[m + 1 == i];
			}
			return ;
		}
		if(m & 1) {
			cout << "YES\n";
			rep(i, 1, m + 1) 
				cout << (i & 1) + 1 << " \n"[m + 1 == i];	
		}
		else if(n > 2) {
			cout << "YES\n";
			rep(k, 1, n) if(!z) {
				rep(i, 1, n) rep(j, 1, n) if(i != j && i != k && j != k) {
					if(a[i][k] == a[k][j]) x = i, y = j, z = k;
				}
			}
			assert(x != y && y != z && x != z);
			if(!((m / 2) & 1)) {
				rep(i, 1, m / 2) cout << ((i & 1)? z : x) << " ";
				cout << z;
				rep(i, 1, m / 2) cout << " " << ((i & 1) ? y : z);
				cout << "\n";
			}
			else {
				rep(i, 1, m / 2) cout << ((i & 1)? x : z) << " ";
				cout << z;
				rep(i, 1, m / 2) cout << " " << ((i & 1) ? y : z);
				cout << "\n";
			}
			
		}
		else cout << "NO\n";
	}

};
using namespace solver;
signed main() {
//	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n, m; cin >> n >> m;
		init_(n, m);
		rep(i, 1, n) rep(j, 1, n) cin >> a[i][j];
		solve();
	}
	return 0;
}
