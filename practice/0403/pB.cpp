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
namespace SOLVE {
	int n;
	stack<pii> st[2];
	vector<vector<int>> aa;
	void init_(int _n) {
		n = _n;
		rep(i, 1, n) rep(j, 1, n) {
			if((i & 1) == (j & 1)) st[0].push({i, j});
			else st[1].push({i, j});
		}
		aa.assign(n + 1, vector<int>(n + 1, 0));
	}
	void solve() {
		rep(i, 1, n * n) {
			int a; cin >> a;
			if(st[0].size() && a != 1) {
				pii cur = st[0].top(); st[0].pop();
				cout << 1 << " " << cur.first << " " << cur.second << "\n";
				aa[cur.first][cur.second] = 1;
				cout.flush();
			}
			else if(st[1].size() && a != 2) {
				pii cur = st[1].top(); st[1].pop();
				cout << 2 << " " << cur.first << " " << cur.second << "\n";
				aa[cur.first][cur.second] = 2;
				cout.flush();
			}
			else {
				int id = st[0].size() ? 0 : 1;
				pii cur = st[id].top(); st[id].pop();
				cout << 3 << " " << cur.first << " " << cur.second << "\n";
				aa[cur.first][cur.second] = 3;
				cout.flush();
			}
		}
		
		return;
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n), solve();
	
	return 0;

}
