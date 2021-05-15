#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimze("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
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
namespace solver {
	int n;
	vector<string> a;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, "");
	}
	string add(string s) {
		int cur = 1;
		reverse(all(s));
		rep(i, 0, signed(s.size()) - 1) {
			int x = cur + s[i] - '0';
			if(x == 10) s[i] = '0', cur = 1;
			else s[i] = char(x + '0'), cur = 0;  
		}
		if(cur) s += "1";
		reverse(all(s));
		return s;
	}
	int solve() {
		int ans = 0;
		rep(i, 2, n) {
			if(a[i].size() > a[i - 1].size()) continue;
			bool yes = 1;
			if(a[i] > a[i - 1].substr(0, a[i].size())) {
				int cnt = signed(a[i - 1].size()) - signed(a[i].size());
				ans += cnt;
				rep(j, 1, cnt) a[i] += "0";
			}
			else if(a[i] < a[i - 1].substr(0, a[i].size())) {
				int cnt = signed(a[i - 1].size()) - signed(a[i].size()) + 1;
				ans += cnt;
				rep(j, 1, cnt) a[i] += "0";
			}
			else {
				string cur = add(a[i - 1]);
				if(cur.size() != a[i - 1].size() || a[i] != cur.substr(0, a[i].size())) {
					int cnt = signed(a[i - 1].size()) - signed(a[i].size()) + 1;
					ans += cnt;
					rep(j, 1, cnt) a[i] += "0";
				}
				else {
					ans += signed(a[i - 1].size()) - signed(a[i].size());
					a[i] = cur;
				}
			}
		}
		vprint(all(a));
		return ans;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n; cin >> n;
		init_(n);
		rep(i, 1, n) cin >> a[i];
		cout << "Case #" << tt << ": " << solve() << "\n";
	}
	return 0;
}
