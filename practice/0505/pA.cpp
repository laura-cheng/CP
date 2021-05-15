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

#define INF 1000000000000000000
#define eps (1e-9)
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n, K;
	vector<string> a;
	unordered_set<string> b;
	void init_(int _n, int _k) {
		n = _n, K = _k;
		a.assign(n + 1, "");
		b.clear();
	} 
	char third(char a, char b) {
		if(a != 'S' && b != 'S') return 'S';
		else if(a != 'E' && b != 'E') return 'E';
		else return 'T';
	}
	int solve() {
		rep(i, 1, n) b.insert(a[i]);
		int ans = 0;
		rep(i, 1, n) rep(j, i + 1, n) {
			string cur = "";
			rep(k, 0, K - 1) {
				if(a[i][k] == a[j][k]) cur += a[i][k];
				else cur += third(a[i][k], a[j][k]);
			}
			print(a[i], a[j], cur);
			if(b.find(cur) != b.end()) ans ++;
		}
		return ans / 3;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	init_(n, k);
	rep(i, 1, n) cin >> a[i];
	cout << solve() << "\n";
	return 0;
} 
