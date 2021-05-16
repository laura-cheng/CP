#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()

#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000000000000
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;

int n;
vector<int> g, best, temp;
vector<vector<int>> ans, mp;
bool cmp(vector<int> a, vector<int> b) {
	vector<int> aa, bb;
	for(auto i : a) aa.push_back(g[i]);
	for(auto i : b) aa.push_back(g[i]);
	for(auto i : b) bb.push_back(g[i]);
	for(auto i : a) bb.push_back(g[i]);
	return aa < bb; 
}
void dfs1(int x, int par) {
	vector<vector<int>> cur;
	for(auto i : mp[x]) {
		if(i == par) continue;
		dfs1(i, x);
		cur.push_back(ans[i]);
	}
	sort(all(cur), cmp);
	ans[x].push_back(x);
	for(auto i : cur) {
		for(auto j : i) {
			ans[x].push_back(j);
		}
	}
	cur.clear();
	return;
}
void dfs2(int x, int par, vector<int> p) {
	vector<vector<int>> cur;
	vector<int> temp;
	int st = 0;
	cur.push_back(vector<int>());
	for(auto i : p) {
		if(st < ans[x].size() && i == ans[x][st]) st ++;
		else cur[0].push_back(i);
	}
	for(auto i : mp[x]) {
		if(i == par) continue;
		cur.push_back(ans[i]);
	}
	sort(all(cur), cmp);
	temp.push_back(x);
	for(auto i : cur) {
		for(auto j : i) {
			temp.push_back(j);
		}
	}
	if(cmp(temp, best)) best = temp;
	for(auto i : mp[x]) {
		if(i == par) continue;
		dfs2(i, x, temp);
	}
	temp.clear(), cur.clear();
	return;
}

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	g.assign(n + 1, 0);
	ans.assign(n + 1, vector<int>());
	mp.assign(n + 1, vector<int>());
	g[0] = INF;
	rep(i, 1, n) cin >> g[i];
	rep(i, 1, n - 1) {
		int a, b; cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	best = vector<int>(n, 0);
	dfs1(1, 1), dfs2(1, 1, vector<int>());
	rep(i, 0, best.size() - 1) {
		cout << g[best[i]] << " \n"[i + 1 == best.size()];
	}
	return 0;
}