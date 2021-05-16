#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int,int>
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
int n, m;
struct edge {
	int to, cost;
};
vector<vector<edge>> mp;
vector<int> cnt, dis;
int spfa(int s, int t) {
	cnt.assign(n + 1, 0);
	dis.assign(n + 1, INF);
	dis[s] = 0;
	queue<int> q; q.push(s);
	while(q.size()) {
		int cur = q.front(); q.pop();
		cnt[cur] ++;
		if(cnt[cur] > n + 1) return -1;
		for(auto i : mp[cur]) {
			if(dis[i.to] > dis[cur] + i.cost) {
				dis[i.to] = dis[cur] + i.cost;
				q.push(i.to);
			}
		}
	}
	return dis[t];
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	mp.assign(n + 1, vector<edge>());
	rep(i, 0, n - 1) {
		mp[i + 1].push_back({i, 0});
		mp[i].push_back({i + 1, 1});
	}
	rep(i, 1, m) {
		int a, b, c; 
		cin >> a >> b >> c;
		mp[a - 1].push_back({b, c});
		mp[b].push_back({a - 1, -c});
	}
	cout << -spfa(n, 0) << " " << spfa(0, n) << "\n";
	return 0;
}
