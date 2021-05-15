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
#define lld lon double
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
namespace solve1 {
	int n;
	vector<vector<int>> mp;
	vector<int> nxt, pre, vis;
	void init_(int _n) {
		n = _n;
		mp.assign(n + 1, vector<int>());
		nxt.assign(n + 1, 0);
		pre.assign(n + 1, 0);
		vis.assign(n + 1, 0);
		rep(i, 0, n) {
			pre[i] = i - 1;
			nxt[i] = i + 1;
		}
	}
	void del(int x) {
		int a = pre[x], b = nxt[x];
		nxt[a] = b, pre[b] = a;
	}
	int solve() {
		queue<int> q; 
		int cnt = 0;
		while(nxt[0] != n + 1) {
			cnt ++, q.push(nxt[0]), del(nxt[0]);
			while(q.size()) {
				stack<int> op;
				int cur = q.front(); q.pop();
				for(auto i : mp[cur]) {
					vis[i] = 1, op.push(i);
				}
				for(int i = nxt[0]; i != n + 1; i = nxt[i]) {
					if(vis[i]) continue;
					del(i), q.push(i);
				}
				while(op.size()) {
					vis[op.top()] = 0;
					op.pop();
				}
			}
		}
		return cnt - 1;
	}
};

using namespace solve1;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; cin >> n >> m;
	init_(n);
	rep(i, 1, m) {
		int a, b; cin >> a >> b;
		mp[a].push_back(b);
		mp[b].push_back(a);
	}
	int ans = solve();
	cout << ans << "\n";
	return 0;
}
