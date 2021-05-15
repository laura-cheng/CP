#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)
#define MOD 1000000007

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace SOLVE {
	int n, m;
	int dirx[] = {1, 0, 0, -1};
	int diry[] = {0, 1, -1, 0};
	vector<vector<int>> a;
	vector<int> dis;
	void init_(int _n, int _m) {
		n = _n, m = _m;
		a.assign(n + 1, vector<int>(m + 1, 0));
		dis.assign(n * m + 1, INF);
	}
	int id(pii x) {
		return (x.first - 1) * m + x.second;
	}
	pii get(int x) {
		if(x % m == 0) return {x / m, m};
		else return {x / m + 1, x % m};
	}
	int solve() {
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		dis[id({1, 1})] = a[1][1]; pq.push({a[1][1], id({1, 1})});
		while(pq.size()) {
			pii cur = pq.top(); pq.pop();
			if(cur.first != dis[cur.second]) continue;
			cur = get(cur.second);
			rep(i, 0, 3) {
				pii nxt = {
					cur.first + dirx[i],
					cur.second + diry[i]	
				};
				if(nxt.first == 0 || nxt.second == 0) continue;
				if(nxt.first > n || nxt.second > m) continue; 
				int v = dis[id(cur)] + a[nxt.first][nxt.second];
				if(v < dis[id(nxt)]) {
					dis[id(nxt)] = v;
					pq.push({v, id(nxt)});
				}
			}
		}
		return dis[id({n, m})];
	
	}
};
using namespace SOLVE;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int t; cin >> t;
	
	while(t--) {
		int n, m; cin >> n >> m;
		init_(n, m);
		rep(i, 1, n) rep(j, 1, m) {
			cin >> a[i][j];
		}
		cout << solve() << "\n";
	}
	
	
	return 0;
}
