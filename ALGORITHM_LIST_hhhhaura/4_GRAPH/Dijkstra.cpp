#define hhhhaura
#include <bits/stdc++.h>
#pragma GC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()  
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef hhhhaura
#define print(a...) out("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {while(L < R) cerr << *L << "\n"[next(L) == R], ++L;}
void out() {cerr << endl;}
template<class T1, class... T2> void out(T1 a, T2 ... e) {cerr << a << " ", out(e...);}
#else
#define print(...) 0
#define vprint(...) 0
#endif
int t, n, m, S, T;
struct edge {
	int t, cost;
};
vector<vector<edge>> mp;
vector<int> d, vis;
int solve(int s, int t) {
	d.assign(n + 1, INF);
	vis.assign(n + 1, 0);
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.push({0, s}), d[s] = 0;
	while(pq.size()) {
		int cur = pq.top().second; pq.pop();
		if(vis[cur]) continue;
		vis[cur] = 1;
		for(auto i : mp[cur]) {
			if(d[i.t] > d[cur] + i.cost) {
				d[i.t] = d[cur] + i.cost;
				pq.push(pii(d[i.t], i.t));
			}
		}
	}
	if(d[t] == INF) return -1;
	else return d[t];

} 

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> t;
	rep(tt, 1, t) {
		cin >> n >> m >> S >> T;
		mp.assign(n + 1, vector<edge>());
		rep(i, 1, m) {
			int a, b, c;
			cin >> a >> b >> c;
			mp[a].push_back({b, c});
			mp[b].push_back({a, c});
		}
		int ans = solve(S, T);
		if(ans == -1) cout << "Case #" << tt << ": " << "unreachable\n";
		else cout << "Case #" << tt << ": " << ans << "\n"; 
	}
	return 0;
}
