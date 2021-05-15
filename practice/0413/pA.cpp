#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
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
	vector<vector<int>> a;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, vector<int>());
		rep(i, 1, n) a[i].push_back(0);
	}
	int solve() {
		int ans = INF;
		rep(i, 1, n) {
			if(a[i].size() < 2) continue;
			a[i].push_back(n + 1);
			int cur = 0;
			rep(j, 1, signed(a[i].size()) - 1) {
				cur += bool(a[i][j] - a[i][j - 1] - 1);
			}
			ans = min(ans, cur);
		}
		return ans;
	}
};
using namespace solver;

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		init_(n);
		rep(i ,1, n) {
			int x; cin >> x;
			a[x].push_back(i);
		}
		cout << solve() << "\n";
	}		
	return 0;
}
