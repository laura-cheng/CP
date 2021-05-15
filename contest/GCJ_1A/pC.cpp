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
	int n, q;
	vector<int> a, score, valid;
	vector<string> s;
	string best;
	pii ans;
	void init_(int _n, int _q) {
		n = _n, q = _q;
		a.assign(n + 1, 0);
		s.assign(n + 1, "");
		score.assign(n + 1, 0);
		valid.clear();
	}
	void build() {
		rep(i, 1, n) {
			rep(j, 0, q - 1) 
				a[i] |= ((s[i][j] == 'T') << j);
		}
	}
	bool check(int x) {
		rep(i, 1, n) {
			int cur = a[i] ^ x;
			if(q - __builtin_popcount(cur) != score[i]) return false;
		}
		return true;
	}
	int cal(int x) {
		int ans = 0;
		rep(i, 0, q - 1) {
			int id = (x >> i) & 1;
			int cnt = 0;
			for(auto j : valid) {
				if(((j >> i) & 1)== id) cnt ++;
			}
			ans += cnt;
		}
		return ans;
	}
	void solve() {
		rep(i, 0, (1 << q) - 1) {
			if(check(i)) valid.push_back(i);
		}
		int temp = 0;
		rep(i, 0, (1 << q) - 1) {
			int cur = cal(i);
			if(cur > temp) {
				temp = cur, best = "";
				rep(j, 0, q - 1) {
					best += (((i >> j) & 1) ? "T" : "F");
				}
			}
 		}
 		int len = valid.size();
 		int gcd = __gcd(temp, len);
		ans = {temp / gcd, len / gcd};
 		return;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, q; cin >> n >> q;
		init_(n, q);
		rep(i, 1, n) cin >> s[i] >> score[i];
		build(), solve();
		cout << "Case #" << tt << ": " << best << " " << ans.first << "/" << ans.second << "\n";
	}
	return 0;
}
