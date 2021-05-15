#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) for(int i = a; i <= b; i++)

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
#define print(a...) kout("[" + string(#a) + "] = ", a )
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ",kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace seg {
	int n;
	vector<int> sum, tag;
	void init_(int _n) {
		n = _n;
		sum.assign(2 * n + 1, 0);
		tag.assign(2 * n + 1, 0);
	}
	inline int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		sum[nd] = {
			sum[lch] + (mid - L + 1) * tag[lch]
			+ sum[rch] + (R - mid) * tag[rch]
		};
	}
	void push(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		sum[nd] += tag[nd] * (R - L + 1);
		tag[lch] += tag[nd], tag[rch] += tag[nd];
		tag[nd] = 0;
	}
	void modify(int L, int R, int l, int r, int val) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		if(L != R) push(L, R);
		if(l <= L && r >= R) tag[nd] += val;
		else {
			modify(L, mid, l, r, val);
			modify(mid + 1, R, l, r, val);
			pull(L, R);
		} 
	}
	int query(int L, int R, int k) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) return (sum[nd] + tag[nd] > k ? L : L + 1);
		else {
			push(L, R);
			int ll = sum[get(L, mid)] + (mid - L + 1) * tag[get(L, mid)];
			if(ll > k) return query(L, mid, k);
			else return query(mid + 1, R, k - ll);
		}
	}
};
namespace solver {
	int n, m, ii;
	vector<int> a;
	struct node {
		int L, R, val;
	};
	vector<node> st;
	void init_(int _n, int _m) {
		n = _n, m = _m, ii = 0;
		a.assign(n + 1, 0);
		st.assign(n + 1, {0, 0, 0});
		seg::init_(n);
	}
	int solve() {
		int ans = 0;
		rrep(i, 1, n) {
			int r = i;
			while(ii && st[ii].val <= a[i]) {
				seg::modify(1, n, st[ii].L, st[ii].R, a[i] - st[ii].val);
				r = st[ii].R, ii --;
			}
			ans += max(0ll, seg::query(1, n, m) - i);
			st[++ii] = {i, r, a[i]};
		}
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;	
	init_(n, m);
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	return 0;
}
