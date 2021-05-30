#define wiwihorz
#include "roads.h"
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

//#define int long long int
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
namespace solver1 {
	vector<ll> minimum_closure_costs(int N, vector<int> U, 
		vector<int> V, vector<int> W) {
		vector<ll> ans(N, 0);
		sort(all(W)), reverse(all(W));
		rrep(i, 0, N - 2) {
			ans[i] = ans[i + 1] + W[i];
		}	
		return ans;
	}

};
//namespace solver2 {
	int n;
	vector<ll> dp[2];
	vector<int> x, y, es, cost;
	vector<vector<int>> mp;
	void dfs(int x, int par, int k) {
		vector<int> v;
		int cnt = 0;
		for(auto i : mp[x]) if(i != par) {
			int to = es[i] ^ x; cnt ++;
			dfs(to, i, k);
			ll cur = cost[i] + min(dp[0][to], dp[1][to]);
			dp[0][x] += cur, dp[1][x] += cur;
			v.push_back(min(0ll, dp[1][to] - cur));
		}
		sort(all(v)); 
		rep(i, 0, min(k - 1, signed(v.size())) - 1) dp[0][x] += v[i], dp[1][x] += v[i];
		if(k - 1 < v.size()) dp[0][x] += v[k - 1];
		return;
	}
	vector<ll> minimum_closure_costs(int N, vector<int> U, 
		vector<int> V, vector<int> W) {
		n = N, x = U, y = V, cost = W;
		es.assign(n - 1, 0);
		mp.assign(n, vector<int>());
		rep(i, 0, n - 2) {
			es[i] = x[i] ^ y[i];
			mp[x[i]].push_back(i);
			mp[y[i]].push_back(i);
		}	
		vector<ll> ans(n, 0);
		rep(i, 0, min(n - 1, 1)) {
			dp[0].assign(n, 0);
			dp[1].assign(n, 0);
			dfs(0, -1, i);
			ans[i] = dp[0][0];
		} 
		return ans;
	}
/*};
using namespace solver2;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	vector<ll> a = minimum_closure_costs(5, {0, 0, 0, 2}, {1, 2, 3, 4}, {1, 4, 3, 2});
	vprint(all(a));
	return 0;
} */
