#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

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
namespace solve_ {
	int n;
	lld start; 
	vector<int> a, c, op1, op2;
	vector<vector<int>> cur, nxt;
	void init_(int _n) {
		n = _n;
		a.assign(2 * n + 1, 0);
		c.assign(2 * n + 1, 0);
		rep(i, 1, 2 * n) c[i] = i;
	}
	void do1(vector<int> &a) {
		rep(i, 1, n) swap(a[i], a[i + n]);
	}
	void do2(vector<int> &a) {
		for(int i = 1; i <= 2 * n - 1; i += 2) {
			swap(a[i], a[i + 1]);
		}
	}
	int solve() {
		op1 = a, op2 = a;
		int cnt = 0;
		if(a == c) return 0;
		start = clock();
		while(clock() - start < 2500) {
			cnt ++;
			if(cnt & 1) do1(op1), do2(op2);
			else do1(op2), do2(op1);
			if(op1 == c || op2 == c) return cnt; 
		}
		return -1;
	}


};
using namespace solve_;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, 2 * n) cin >> a[i];
	cout << solve() << "\n";
	
	return 0;
}
