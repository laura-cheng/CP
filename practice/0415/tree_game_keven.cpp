#include<bits/stdc++.h>
#define pb emplace_back
#define AI(i) begin(i), end(i)
using namespace std;
using ll = long long;
template<class T> bool chmin(T &a, T b) { return b < a && (a = b, true); }
template<class T> bool chmax(T &a, T b) { return a < b && (a = b, true); }
#ifdef KEV
#define DE(args...) kout("[ " + string(#args) + " ] = ", args)
void kout() {cerr << endl;}
template<class T, class ...U> void kout (T v, U ...e) { cerr << v << ' ', kout(e...); }
template<class T> void debug(T L, T R) { while (L != R) cerr << *L << " \n"[next(L)==R], ++L; }
#else
#define DE(...) 0
#define debug(...) 0
#endif
// What I should check
// 1. overflow
// 2. corner cases
// Enjoy the problem instead of hurrying to AC
// Good luck !
const int MAX_N = 300010, inf = 1e9;

int n, dp1[MAX_N], dp2[MAX_N], dp3[MAX_N];

vector<int> edge[MAX_N];

void dfs(int x, int lst) {
	for (int u : edge[x]) if (u != lst) {
		dfs(u, x);
	}

	int tmp1[3]{0, -inf, -inf}, tmp2[3];

	for (int u : edge[x]) if (u != lst) {
		dp1[x] += max({dp2[u]+1, dp3[u]});

		fill(tmp2, tmp2 + 3, -inf);
		for (int i = 0;i < 3;++i) {
			chmax(tmp2[i], tmp1[i] + dp3[u]);
			chmax(tmp2[ min(2, i+1) ], tmp1[i] + max(dp1[u], dp2[u]));
		}
		swap(tmp1, tmp2);
	}

	dp2[x] = max(tmp1[1], tmp1[2]);
	dp3[x] = max<ll>(0, tmp1[2] + 1);

	DE(x, dp1[x], dp2[x], dp3[x]);


}
int32_t main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int a, b, i = 1;i < n;++i) {
		cin >> a >> b;
		edge[a].pb(b), edge[b].pb(a);
	}

	dfs(1, 1);

	cout << max({dp1[1], dp2[1], dp3[1]}) << '\n';
}

