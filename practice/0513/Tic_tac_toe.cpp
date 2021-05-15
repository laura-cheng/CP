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
void kout() { cerr << endl;} 
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int row[2][3], col[2][3], dia[2][3];
	int cnt[2], win[2];
	void init_() {
		rep(i, 0, 2) {
			row[0][i] = row[1][i] = 0;
			col[0][i] = col[1][i] = 0;
			dia[0][i] = dia[1][i] = 0;
		}	
		cnt[0] = cnt[1] = 0;
		win[0] = win[1] = 0;
	}
	int solve() {
		rep(i, 0, 2) rep(j, 0, 2) {
			char x; cin >> x;
			if(x == '_') continue;
			int id = (x == 'X' ? 0 : 1);
			if(i + j == 2) dia[id][0] ++;
			if(i == j) dia[id][1] ++;
			cnt[id] ++;
			col[id][j] ++;
			row[id][i] ++;
			
		}
		rep(j, 0, 1) {
			rep(i, 0, 1) win[j] += (dia[j][i] == 3);
			rep(i, 0, 2) {
				win[j] += (row[j][i] == 3);
				win[j] += (col[j][i] == 3);
			}
		}
		if(cnt[0] < cnt[1] || cnt[0] - cnt[1] > 1) return 3;
		if((win[0] && win[1] > 1) || 
			(win[0] && cnt[0] == cnt[1]) ||
			(win[1] && cnt[0] > cnt[1])) return 3;
		if(cnt[0] + cnt[1] == 9 || win[0] || win[1]) return 1;
		return 2;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		init_();
		cout << solve() << "\n";
	}
	return 0;
}
