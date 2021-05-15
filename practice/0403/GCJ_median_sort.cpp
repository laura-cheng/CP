#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

#define int long long int 
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
random;
namespace solve_ {
	int n;
	vector<int> a;
	void init_(int _n) {
		n = _n;
		rep(i, 1, n) a.push_back(i);
	}
	int ask(int a, int b, int c) {
		cout << a << " " << b << " " << c << "\n";
		cout.flush();
		int ans; cin >> ans;
		return ans;
	}
	void solve(int l, int r, int tp, int id) {
		if(l >= r) return;
		
		vector<int> b[3];
		int piv1 = a[rnd() % (r - l + 1) + l];
		int piv2 = a[rnd() % (r - l + 1) + l];
		while(piv2 == piv1) piv2 = a[rand() % (r - l + 1) + l];
		if(tp == 1) {
			int mid = ask(piv1, piv2, id);
			if(mid == piv1) swap(piv1, piv2);
		}
		else if(tp == 2) {
			int mid = ask(id, piv1, piv2);
			if(mid == piv2) swap(piv1, piv2);
		}
		rep(i, l, r) {
			if(a[i] == piv1 || a[i] == piv2) continue;
			int mid = ask(piv1, piv2, a[i]);
			if(mid == piv1) b[0].push_back(a[i]);
			else if(mid == piv2) b[2].push_back(a[i]);
			else b[1].push_back(a[i]);
		}
		int ii = l, pre = l;
		rep(i, 0, signed(b[0].size()) - 1) a[ii ++] = b[0][i];
		solve(pre, ii - 1, 1, piv1);
		a[ii ++] = piv1, pre = ii;
		rep(i, 0, signed(b[1].size()) - 1) a[ii ++] = b[1][i];
		solve(pre, ii - 1, 1, piv2);
		a[ii ++] = piv2, pre = ii;
		rep(i, 0, signed(b[2].size()) - 1) a[ii ++] = b[2][i];
		solve(pre, ii - 1, 2, piv2);
		return;
	}
};
using namespace solve_;
signed main() {
	int t, n, q, x; 
	cin >> t >> n >> q;
	while(t -- ) {
		init_(n);
		solve(0, n - 1, -1, -1);
		rep(i, 0, n - 1) cout << a[i] << " \n"[i + 1 == n];
		cin >> x;
	}
	return 0;

}
