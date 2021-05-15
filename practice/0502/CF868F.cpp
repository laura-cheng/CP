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
	int n, k, cur, ll, rr;
	vector<int> a, dp1, dp2, cnt;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, 0);
		dp1.assign(n + 1, INF);
		dp2.assign(n + 1, INF);
		cnt.assign(n + 1, 0);
		ll = 1, rr = 0, cur = 0;
	}
	void add(int x) {
		int num = a[x];
		cur += cnt[num];
		cnt[num] ++;
	}
	void minu(int x) {
		int num = a[x];
		cnt[num] --;
		cur -= cnt[num];
	}
	void move(int L, int R) {
		while(ll > L) add(--ll);
		while(ll < L) minu(ll ++);
		while(rr < R) add(++rr);
		while(rr > R) minu(rr--);
	}
	void dc(int L, int R, int l, int r) {
		if(L > R) return;
		int mid = (L + R) / 2;
		move(l + 1, mid);
		int best = l, best_ans = dp1[l] + cur;
		rep(i, l + 1, min(mid - 1, r)) {
			minu(ll), ll++;
			if(best_ans > cur + dp1[i]) {
				best_ans = cur + dp1[i];
				best = i;
			}
		}
		dp2[mid] = best_ans;
		move(l, mid - 1);
		dc(L, mid - 1, l, best);
		move(best, R);
		dc(mid + 1, R, best, r);
		return;		
	}
	int solve() {
		dp1[0] = 0;
		rep(i, 1, k) {
			dc(1, n, 0, n - 1);
			swap(dp1, dp2);
		}	
		return dp1[n];
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) {
		int x; cin >> x;
		a[i] = x;
	}
	cout << solve() << "\n";
	return 0;
}

