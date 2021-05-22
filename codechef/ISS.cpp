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
	const int P = 4 * 1e6 + 10;
	vector<int> phi, f, fac, p;
	void init_() {
		phi.assign(P + 1, 0);
		fac.assign(P + 1, 1);
		f.assign(P + 1, 0);
		p.clear();
		rep(i, 2, P) {
			if(fac[i] == 1) {
				p.push_back(i);
				phi[i] = i - 1;
			}
			for(auto j : p) {
				if(i * j > P) break;
				phi[i * j] = phi[i] * phi[j];
				fac[i * j] = j;
				if(i % j == 0) {
					phi[i * j] = phi[i] * j;
					break;
				}
			}
		}
		rep(i, 1, P / 4) f[4 * i + 1] = 4 * i + 1;
		rep(i, 1, P) for(int j = i; j <= P; j += i) {
			int id = (j - 1) / 4;
			if(4 * id + 1 != j) continue;
			f[j] += phi[j / i] * i;
		}
		return;
	}
	int solve(int k) {
		return f[4 * k + 1] - 1 - (f[4 * k + 1] - 4 * k - 1) / 2;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	init_();
	while(t--) {
		int k; cin >> k;
		cout << solve(k) << "\n";
	}
	return 0;
}
