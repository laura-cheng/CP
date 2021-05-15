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
namespace solver {
	int n, m;
	vector<set<int>> b, a;
	set<pii> mn;
	vector<int> ans, cnt;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(m + 1, set<int>());
		b.assign(n + 1, set<int>());
		ans.assign(m + 1, 0);
		cnt.assign(n + 1, 0);
		mn.clear();
	}
	void solve() {
		rep(i, 1, n) if(b[i].size() > 0) 
			mn.insert({b[i].size(), i});
		rep(i, 1, m) {
			auto it = mn.begin();
			if(mn.size() == 0) {
				cout << "NO\n";
				return;
			}
			if(cnt[it -> second] + 1 > ceil(m , 2)) {
				for(auto j : b[it -> second]) {
					a[j].erase(a[j].find(it -> second));
				}				
				mn.erase(it);
				i --;
				continue;
			}
			int cur = *b[it -> second].begin();
			ans[cur] = it -> second;
			cnt[it -> second] ++;
			for(auto j : a[cur]) {
				auto temp = mn.find(pii(b[j].size(), j));
				b[j].erase(b[j].find(cur));
				int num = temp -> first;
				mn.erase(temp);
				
				if(num > 1) {
					mn.insert({num - 1, j});
				}
			}
		}
		cout << "YES\n";
		rep(i, 1, m) cout << ans[i] << " \n"[i == m];
		return;
	}

};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n, m; cin >> n >> m;
		init_(n, m);
		rep(i, 1, m) {
			int k; cin >> k;
			rep(j ,1, k) {
				int x; cin >> x;
				a[i].insert(x);
				b[x].insert(i);
			}
		}
		solve();
	}
	return 0;
}
