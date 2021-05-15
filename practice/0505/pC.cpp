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

#define int long long int
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
	int a(int x) {
		cout << "? " << x << "\n";
		cout.flush();
		int y; cin >> y;
		return y;
	}
	void report(int x) {
		cout << "! " << x << "\n";
		cout.flush();
		return;
	}
	void solve() {
		int l = 1, r = n / 2 + 1;
		int lv = a(1) - a(n / 2 + 1), rv = -lv;
		if(lv == 0) report(1);
		else if((n >> 1) & 1) report(-1);
		else {
			while(r - l > 1) {
				int mid = (l + r) / 2;
				int val = a(mid) - a(mid + n / 2);
				if(val == 0) {
					report(mid);
					return;
				}
				else if(val * lv > 0) l = mid;
				else r = mid;
			}
			report(-1);
		}
	}
};
using namespace solver;
signed main() {
	cin >> n;
	solve();
	return 0;
} 
