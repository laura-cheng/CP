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
	int n, ii;
	vector<vector<int>> mp;
	vector<int> n1, n2;
	vector<int> a, b, id;
	vector<multiset<int>> need, rneed;
	void init_(int _n) {
		n = _n, ii = 1;
		mp.assign(n + 1, vector<int>());
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		id.assign(n + 1, 0);
		need.assign(n + 1, multiset<int>());
		rneed.assign(n + 1, multiset<int>());
		n1.assign(n + 1, 0);
		n2.assign(n + 1, 0);
		rep(i, 1, n) n1[i] = n2[i] = i;
	}
	bool dfs(int x, int par) {
		pii ans = {0, 0};
		int cnt = 0, y = 1, ch = x;
		for(auto i : mp[x]) {
			if(i == par) continue;
			if(!dfs(i, x)) return 0;
			if(need[n1[i]].size() || rneed[n2[i]].size()) {
				cnt ++;
				if(cnt > 1) return 0;
				else ch = i;
				id[x] = id[i];
			}
		}
		int ch1 = n1[ch], ch2 = n2[ch];
		auto it1 = need[ch1].find(a[x]);
		if(it1 != need[ch1].end()) need[ch1].erase(it1);
		else rneed[ch2].insert(a[x]);
		
		auto it2 = rneed[ch2].find(b[x]);
		if(it2 != rneed[ch2].end()) rneed[ch2].erase(it2);
		else need[ch1].insert(b[x]);
		n1[x] = ch1, n2[x] = ch2;
		if(!id[x]) id[x] = ii++;
		return 1;
	}
	int dp(int x, int par) {
		int ans = 1, cnt = 1, ch = 0;
		for(auto i : mp[x]) {
			if(i == par) continue;
			if(id[x] == id[i]) ch = 1;
		}
		for(auto i : mp[x]) {
			if(i == par) continue;
			cnt ++;
			ans = ans * dp(i, x) % MOD;
		}
		if(!ch) ans = ans * cnt % MOD;
		return ans;
	}
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n, s; cin >> n >> s;
		init_(n);
		rep(i ,1, n - 1) {
			int a, b; cin >> a >> b;
			mp[a].push_back(b);
			mp[b].push_back(a);
		}
		rep(i ,1, n) cin >> a[i];
		rep(i, 1, n) cin >> b[i];
		bool cur = dfs(1, 1);
		if(!cur || need[n1[1]].size() || rneed[n2[1]].size()) {
			cout << "0\n";
		}
		else {
			int ans = dp(1, 1);
			cout << (s == 1 ? bool(ans) : ans) << "\n";	
		}
		
	}
	return 0;
}
