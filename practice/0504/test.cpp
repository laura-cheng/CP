#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b;i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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
	vector<int> nums;
	int len(int x) {
		int cnt = 0;
		while(x) cnt ++, x /= 10;
		return cnt;
	}
	int pow_(int x, int times) {
		int ans = 1;
		for(;times > 0; times >>= 1, x = x * x)	{
			if(times & 1) ans = ans * x;
		}
		return ans;
	}
	int cat(int x, int num) {
		int ans = 0, cnt = 0, cur;
		rep(i, 0, num - 1) {
			cur = len(x + i);
			cnt += cur;
			ans *= pow_(cur);
			ans += x + i;
		}
		return (cnt > 18 ? 0 : ans);
	}
	void init_() {
		nums.clear();
		rep(i, 1, 2000000) {
			int l = len(i);
			rep(j, 3, 18 / l) {
				cur = car(i, j);
				if(cur) nums.push_back(cur);
			}
		}	
		sort(all(nums));
		return;
	}
	int solve(int x) {
		vector<int> All;
		All.push_back(*lower_bound(nums.begin(), nums.end(), x));
		int l = len(x);
		All.push_back(cat(x / pow_(10, ceil(l, 2)), 2));
		All.push_back(cat(x / pow_(10, ceil(l, 2)) + 1, 2));
		All.push_back(cat(x / pow_(10, l / 2), 2));
		All.push_back(cat(pow_(10, ceil(l, 2) - 1, 2));
		sort(all(All));
		for(auto i : All) {
			if(i >= x) return i;
		}
	}
	

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	init_();
	rep(tt, 1, t) {
		int x; cin >> x;
		cout << "Case #" << tt << ": " << solve(x) << "\n";
	}
	return 0;
}

