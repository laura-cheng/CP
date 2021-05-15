#define wiwihorz
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i ,a, b) for(int i = a; i <= b; ++i)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

using namespace std;
using namespace __gnu_pbds;

#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	const int MAXN = 50000;
	int n;
	string a, b;
	bitset<MAXN> A[10], B[10];
	int solve() {
		int mx = 0;
		rep(i, 0, n - 1) {
			int aa = a[i] - 'a', bb = b[i] - 'a';
			A[aa][i] = 1;
			B[bb][i] = 1;
			mx = max({mx, aa, bb});
		}
		int ans = 0;
		rep(i, 0, n - 1) {
			int cnt = 0, cnt1 = 0;
			rep(j, 0, mx) {
				cnt += (A[j] & (B[j] << i)).count();
				cnt1 += ((A[j] << i) & B[j]).count();
			}
			ans = max({ans, cnt, cnt1});
		}
		return ans;
	}	
};
namespace solver1 {
	int n;
	string a, b;
	int solve() {
		int ans = 0;
		rep(i, 0, n - 1) {
			int cnt = 0, cnt1 = 0;
			rep(j, 0, n - 1 - i) {
				cnt += bool(a[j] == b[i + j]);
				cnt1 += bool(a[i + j] == b[j]);
			}
			ans = max({ans, cnt, cnt1});
		}
		return ans;
	}
};
using namespace solver1;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> a >> b, n = a.size();
	cout << solve() << "\n";
	return 0;
}

