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
namespace solver {
	int n;
	vector<int> d, v, pre;
	vector<pii> p;
	void init_(int _n) {
		n = _n;
		d.assign(n + 1 ,0);
		v.assign(n + 1, 0);
		pre.assign(n + 1, 0);
	}
	void solve() {
		rep(i, 1, n) pre[i] = pre[i - 1] + d[i];
		rep(i, 1, n) {
			int l = i, r = n + 1;
			while(r - l > 1) {
				int mid = (l + r) / 2;
				if(pre[mid] - pre[i] >= v[i]) r = mid;
				else l = mid;
			}
			p.push_back({l, i});
		}
		sort(all(p));
		int sum = 0, ii = 0;
		rep(i, 1, n) {
			while(ii < p.size() && p[ii].first < i) {
				int id = p[ii].second;
				sum -= (v[id] - pre[i - 1] + pre[id]);
				ii ++;
			}
			sum += v[i];
			sum -= (i - 1 - ii) * d[i];
			cout << sum << "\n";
		}
		return;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int D; cin >> D;
	init_(D);
	rep(i, 1, n) cin >> v[i] >> d[i];
	solve();
	return 0;
}
