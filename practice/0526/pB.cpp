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
#define MOD 1000000007
#define eps (1e-9)

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
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int a, b, c; cin >> a >> b >> c;
	vector<int> A(a, 0), B(b, 0), C(c, 0);
	for(auto &i : A) cin >> i;
	for(auto &i : B) cin >> i;
	for(auto &i : C) cin >> i;
	vector<int> v; 
	int ans = 0, aa = accumulate(all(A), 0ll);
	int bb = accumulate(all(B), 0ll), cc = accumulate(all(C), 0ll);
	ans = aa + bb + cc;
	print(aa, bb, cc);
	v.push_back(aa);
	v.push_back(bb);
	v.push_back(cc);
	v.push_back(*min_element(all(A)) + *min_element(all(B)));
	v.push_back(*min_element(all(B)) + *min_element(all(C)));
	v.push_back(*min_element(all(C)) + *min_element(all(A)));
	sort(all(v));
	cout << ans - 2 * v[0] << "\n";
	
	return 0;
}
