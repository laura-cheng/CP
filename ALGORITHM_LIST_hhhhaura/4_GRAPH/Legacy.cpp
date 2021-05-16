#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)
#define INF 1000000000000000000

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("["+ string(#a) + "] = ", a)
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
struct LEGACY {
	int n, ii;
	struct edge {
		int to, cost;
	};
	vector<int> in, out;
	vector<vector<edge>> mp;
	vector<int> dis;
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void init_(int _n) {
		n = _n, ii = 0;
		mp.assign(4 * n + 5, vector<edge>());
		in.assign(2 * n + 1, 0);
		out.assign(2 * n + 1, 0);
		build(1, n);
	}
	void build(int L, int R) {
	
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		if(L == R) in[nd] = out[nd] = ++ii;
		else {
			build(L, mid), build(mid + 1, R);
			in[nd] = ++ii; // arrrrrrrrr
			mp[ii].push_back({in[lch], 0});
			mp[ii].push_back({in[rch], 0});
			out[nd] = ++ii;
			mp[out[lch]].push_back({ii, 0});
			mp[out[rch]].push_back({ii, 0});
		}
		return;
	}
	void modify(int L, int R, int l, int r, int u, int tp, int w) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) {
			if(tp == 1) mp[out[nd]].push_back({in[get(u, u)], w});
			else mp[out[get(u, u)]].push_back({in[nd], w });
		}
		else {
			modify(L, mid, l, r, u, tp, w);
			modify(mid + 1, R, l, r, u, tp, w);
		}
	
	}
	void add2(int u, int L, int R, int w) {
		modify(1, n, L, R, u, 2, w);
	}
	void add1(int L, int R, int u, int w) {
		modify(1, n, L, R, u, 1, w);
	}
	void solve(int s) {
		dis.assign(ii + 1, INF);
		dis[in[get(s, s)]] = 0;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.push({0, in[get(s, s)]});
		while(pq.size()) {
			pii p = pq.top(); pq.pop();
			if(dis[p.second] != p.first) continue;
			int cur = p.second;
			for(auto i : mp[cur]) {
				int v = i.cost + dis[cur];
				if(v < dis[i.to]) {
					dis[i.to] = v;
					pq.push({v, i.to});
				}
			}
		}
		return;
	} 
 
} legacy;
int n, q, s;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> q >> s, legacy.init_(n);
	rep(i, 1, q) {
		int t, L, R, u, v, w;
		cin >> t;
		if(t == 1) {
			cin >> u >> v >> w;
			legacy.add1(u, u, v, w);
		}
		else if(t == 2) {
			cin >> v >> L >> R >> w;
			legacy.add2(v, L, R, w);
		}
		else {
			cin >> v >> L >> R >> w;
			legacy.add1(L, R, v, w);
		}
	}
	legacy.solve(s);
	rep(i, 1, n) {
		int id = legacy.in[legacy.get(i, i)];
		if(legacy.dis[id] == INF) cout << "-1";
		else cout << legacy.dis[id];
		cout << " \n"[i == n];
	}
	return 0;
}

/*
4 1 1
3 4 1 3 12
2 2 3 4 10
1 2 4 16
*/
