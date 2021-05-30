#define wiwihorz
#include "hexagon.h"
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

#define ll long long int 
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
#define x first
#define y second

//namespace solver1 {
	int draw_territory(int N, int A, int B, vector<int> D, vector<int> L) {
		assert(N == 3);
		ll ans = 0, n = L[0] + 1, inv2 = 500000004, inv6 = 166666668;
		ans = (A - B) * n % MOD * (n + 1) % MOD * inv2 % MOD;
		ans = (ans + B * n % MOD * (n + 1) % MOD * (2 * n + 1) % MOD * inv6 % MOD);
		return (ans % MOD + MOD) % MOD;
	}

/*};

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cout << draw_territory(3, 100000, 23124, {1, 2, 3}, {10000000, 100000000, 100000000} );
	return 0;
} */
