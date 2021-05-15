//#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

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
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct Dinic {
	struct edge {
		int to, cap, rev;
	};
	int n, s, t;
	vector<vector<edge>> mp;
	vector<int> iter, level;
	void init_(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		iter.assign(n + 1, 0);
		level.assign(n + 1, -1);
		mp.assign(n + 1, vector<edge>());	
	}
	void add_edge(int u, int v, int cap) {
		mp[u].push_back({v, cap, signed(mp[v].size())});
		mp[v].push_back({u, 0, signed(mp[u].size()) - 1});
	}
	bool bfs() {
		level.assign(n + 1, -1);
		queue<int> q;
		q.push(s), level[s] = 0;
		while(q.size()) {
			int cur = q.front(); q.pop();
			for(auto i : mp[cur]) {
				if(level[i.to] != -1 || i.cap <= 0) continue;
				level[i.to] = level[cur] + 1;
				q.push(i.to);
			}
		}
		return level[t] != -1;
	}
	int dfs(int s, int t, int flow) {
		if(s == t) return flow;
		for(int &i = iter[s]; i < mp[s].size(); i++) {
			edge &es = mp[s][i];
			if(level[es.to] != level[s] + 1 || es.cap <= 0) continue;
			int ans = dfs(es.to, t, min(flow, es.cap));
			if(ans > 0) {
				es.cap -= ans;
				mp[es.to][es.rev].cap += ans;
				return ans;
			}				
		}
		return 0;
	}
	int solve() {
		int ans = 0, cur = 0;
		while(bfs()) {
			iter.assign(n + 1, 0);
			while((cur = dfs(s, t, INF)) > 0) {
				ans += cur;
			}
		}
		return ans;
	}
};
namespace SOLVE {
	int n, m, s, t;
	Dinic a;
	void init_(int _n, int _m, vector<int> cnt) {
		n = _n, m = _m;
		s = n + m + 1;
		t = n + m + 2;
		a.init_(n + m + 2, s, t);
		rep(i, 1, m) a.add_edge(s, i + n, cnt[i]);
		rep(i, 1, m) a.add_edge(i + n, t, 1);
	}
	void add_person(int id, vector<int> cnt) {
		rep(i, 1, m) {
			if(cnt[i] > 1) a.add_edge(id, i + n, cnt[i] - 1);
			else if(cnt[i] == 0) a.add_edge(i + n, id, 1);
		}
	}
	int solve() {return a.solve();}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	rep(tt, 1, t) {
		int n, m, k; 
		
		cin >> n >> m >> k;
		vector<int> cur(m + 1, 0);
		rep(i, 1, k) {
			int x; cin >> x;
			cur[x] ++;
		}
		init_(n - 1, m, cur);
		rep(i, 1, n - 1) {
			cin >> k;
			cur.assign(m + 1, 0);
			rep(j, 1, k) {
				int x; cin >> x;
				cur[x] ++;
			}
			add_person(i, cur);
		}
		cout << "Case #" << tt << ": " << solve() << "\n";
	}
	return 0;
}
