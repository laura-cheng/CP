#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define INF 1e18ll
#define MOD 1000000007
#define eps (1e-9)


#define int long long int
#define lld long double
#define pii pair<int, int> 

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, m, ii, cur, q;
vector<int> p, c, d, ans, vis, match;
vector<vector<int>> mp;
set<int> s;
void init_() {
	cur = 0, ii = 0;
	mp.assign(5001, vector<int>());
	vis.assign(m + 1, 0);
	match.assign(m + 1, -1);
	p.assign(n + 1, 0);
	c.assign(n + 1, 0);
	return;
}
bool dfs(int x) {
	for(auto i : mp[x]) {
		if(vis[i] == ii) continue;
		vis[i] = ii;
		if(match[i] == -1 || dfs(match[i])) {
			match[i] = x;
			return true;
		}
	}
	return false;
}
void add(int x) {
	mp[p[x]].push_back(c[x]);
	while(cur <= 5000 && ++ii && dfs(cur)) {
		cur ++;
	}
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m, init_();
	rep(i, 1, n) cin >> p[i];
	rep(i, 1, n) cin >> c[i];
	cin >> q;
	rep(i, 1, q) {
		int x; cin >> x;
		d.push_back(x);
		s.insert(x);
	}
	reverse(all(d));
	rep(i, 1, n) {
		if(!s.count(i)) add(i);
	}
	for(auto i : d) {
		ans.push_back(cur);
		add(i);
	}
	reverse(all(ans));
	rep(i, 0, q - 1) {
		cout << ans[i] << "\n";
	}
	return 0;
}