#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld lon double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a) 
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace SOLVE {
	int n; string s;
	vector<int> pre[2];
	void init_(int _n, string _s) {
		n = _n, s = _s;
		pre[0].assign(n + 1, 0);
		pre[1].assign(n + 1, 0);
		s.insert(0, "0");
		rep(i, 1, n) {
			pre[0][i] = pre[0][i - 1] + bool(s[i] == '-');
			pre[1][i] = pre[1][i - 1] + bool(s[i] == '+'); 
		}
	}
	int query(int l, int r) {
		int plus = pre[1][n] - (pre[1][r] - pre[1][l - 1]);
		int minu = pre[0][n] - (pre[0][r] - pre[0][l - 1]);
		if(!(plus + minu)) return 1;
		else return 1 + abs(plus - minu);
	}

};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n, m; cin >> n >> m;
		string s; cin >> s;
		init_(n, s);
		rep(i, 1, m) {
			int l, r; cin >> l >> r;
			cout << query(l, r) << "\n";
		}
	}
	
	return 0;
}
