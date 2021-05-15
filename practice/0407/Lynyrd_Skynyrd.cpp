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
	int n, m, lg_n, lg_m;
	vector<int> a, b, p;
	vector<vector<int>> pos, ac, sp;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		lg_n = 31 - __builtin_clz(n);
		lg_m = 31 - __builtin_clz(m);
		p.assign(n + 1, 0);
		b.assign(n + 1, 0);
		a.assign(m + 1, 0);
		pos.assign(n + 1, vector<int>());
		ac.assign(lg_n + 1, vector<int>(m + 2, 0));
		sp.assign(lg_m + 1, vector<int>(m + 1, 0));
	}
	void build() {
		rep(i, 1, n) b[p[i]] = i;
		rep(i, 1, m) pos[a[i]].push_back(i);
		rep(i, 1, m) {
			int nxt = p[(b[a[i]] % n) + 1];
			int id = lower_bound(pos[nxt].begin(), pos[nxt].end(), i) - pos[nxt].begin();
			if(id == pos[nxt].size()) ac[0][i] = m + 1;
			else ac[0][i] = pos[nxt][id];
		}
		ac[0][m + 1] = m + 1;
		rep(i, 1, lg_n) rep(j, 1, m + 1) {
			ac[i][j] = ac[i - 1][ac[i - 1][j]];
		}
		rep(i, 1, m) {
			int x = i;
			rep(j, 0, lg_n) if(((n - 1) >> j) & 1) {
				x = ac[j][x];
			}
			sp[0][i] = x;
		}
		rep(i, 1, lg_m) rep(j, 1, m) {
			sp[i][j] = min(sp[i - 1][j], sp[i - 1][min(m, j + (1 << (i - 1)))]);
		}
		return;
	}
	bool query(int l, int r) {
		int lg = 31 - __builtin_clz(r - l + 1);
		return min(sp[lg][l], sp[lg][r - (1 << lg) + 1]) <= r;
	}
};
using namespace solve_;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m, q; 
	cin >> n >> m >> q;
	init_(n, m);
	rep(i, 1, n) cin >> p[i];
	rep(i, 1, m) cin >> a[i];
	build();
	string ans;
	rep(i, 1, q) {
		int l, r; cin >> l >> r;
		ans += char('0' + query(l, r));
	}
	cout << ans << "\n";
	return 0;

}
