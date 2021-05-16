//#define wiwihorz
#include <vector>
#include <cstdio>
#include <algorithm>
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
vector<int> L, D, x, y, es, ans;
vector<vector<int>> mp;
int timestamp = 0;
void init_(int n) {
	L.assign(n, 0);
	D.assign(n, 0);
	x.clear(), y.clear();
	es.clear(), ans.clear();
	mp.assign(n, vector<int>());
	timestamp = 0;
	return;
}
void add_edge(int a, int b) {
	x.push_back(a);
	y.push_back(b);
	es.push_back(a ^ b);
	mp[a].push_back(x.size() - 1);
	mp[b].push_back(y.size() - 1);
	return;
}
bool cmp(int a, int b) {
	if(x[a] == x[b]) return y[a] < y[b];
	else return x[a] < x[b];
}
void dfs(int x, int par) {
	L[x] = D[x] = ++timestamp;
	for(auto i : mp[x]) {
		if(i == par) continue;
		int to = es[i] ^ x;
		if(!D[to]) {
			dfs(to, i);
			L[x] = min(L[x], L[to]);
		} 
		else L[x] = min(L[x], D[to]);
		if(L[to] > D[x]) ans.push_back(i);
		
	} 
	return;
}
signed main() {
	int n;
	while(scanf("%lld", &n) == 1) {
		init_(n); 
		rep(i, 1, n) {
			int x, y, m;
			scanf("%lld (%lld)", &x, &m);
			rep(j, 1, m) {
				scanf("%lld", &y);
				if(x < y) add_edge(x, y);
			}
		}
		rep(i, 0, n - 1) {
			if(!D[i]) dfs(i, -1);
		}
		sort(all(ans), cmp);
		int aa = ans.size();
		printf("%lld critical links\n", aa);
		for(auto i : ans) {
			printf("%lld - %lld\n", x[i], y[i]);
		}
		printf("\n");
	}
	return 0;
}
