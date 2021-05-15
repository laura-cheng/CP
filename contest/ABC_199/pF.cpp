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
struct mat {
	int n;
	vector<vector<int>> v;
	void init_(int _n) {
		n = _n;
		v.assign(n + 1, vector<int>(n + 1, 0));
	}
	void id() {
		rep(i, 1, n) v[i][i] = 1;
	}
	mat operator*(mat b) {
		mat ans; ans.init_(b.n);
		rep(i, 1, n) rep(j, 1, n) {
			rep(k, 1, n) {
				ans.v[i][j] = (ans.v[i][j] + 
					v[i][k] * b.v[k][j] % MOD) % MOD;
			}
		}
		return ans;
	}
};
namespace solver {
	int n, m, k;
	vector<vector<int>> mp;
	vector<int> a;
	void init_(int _n, int _m, int _k) {
		n = _n, m = _m, k = _k;
		mp.assign(n + 1, vector<int>());
		a.assign(n + 1, 0);
	}
	int pow_(int a, int times) {
		int ans = 1;
		for(; times > 0; times >>= 1, a = a * a % MOD) {
			if(times & 1) ans = ans * a % MOD;
		}
		return ans;
	}
	void solve() {
		mat s, ans; 
		s.init_(n), ans.init_(n), ans.id();
		int invM = pow_(m, MOD - 2), inv2 = pow_(2, MOD - 2);
		rep(i, 1, n) {
			s.v[i][i] = 1 - invM * mp[i].size() % MOD * inv2 % MOD;
			for(auto j : mp[i]) {
				s.v[i][j] = invM * inv2 % MOD;
			}
		}
		for(; k > 0; k >>= 1, s = s * s) {
			if(k & 1) ans = ans * s;
		}
		rep(i, 1, n) {
			int cur = 0;
			rep(j, 1, n) {
				cur += a[j] * ans.v[i][j];
				cur %= MOD;
			}
			cout << (cur % MOD + MOD) % MOD << "\n";
		}
		
	}
	
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, k; cin >> n >> m >> k;
	init_(n, m, k);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, m) {
		int x, y; cin >> x >> y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	solve();
	return 0;
}
