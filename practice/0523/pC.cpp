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
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	struct es {
		int from, to, cost;
	};
	vector<es> a, b;
	vector<int> bal, pos, neg;
	void init_(int _n) {
		n = _n;
		a.clear(), b.clear();
		bal.assign(n + 1, 0);
		pos.clear(), neg.clear();
	}
	void solve() {
		for(auto i : a) {
			bal[i.from] -= i.cost;
			bal[i.to] += i.cost;
		}
		rep(i, 1, n) {
			if(bal[i] > 0) pos.push_back(i);
			else neg.push_back(i); 
			bal[i] = abs(bal[i]);
		}
		int cnt = 0;
		for(auto i : neg) {
			while(bal[i]) {
				int v = min(bal[pos[cnt]], bal[i]);
				b.push_back({i, pos[cnt], v});
				bal[pos[cnt]] -= v;
				bal[i] -= v;
				if(!bal[pos[cnt]]) cnt++;
			}
		}
		cout << b.size() << "\n";
		for(auto i : b) cout << i.from << " " << i.to
			<< " " << i.cost << "\n";
		return;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int x, y, z;
		cin >> x >> y >> z;
		a.push_back({x, y, z});
	}
	solve();
	return 0;
} 

