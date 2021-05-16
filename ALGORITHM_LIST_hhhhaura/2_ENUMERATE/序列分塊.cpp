#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000000000000
#define eps (1e-9)
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

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
int n, m,sz, bk;
vector<int> a, cnt, to;
void build(int i) {
	int l = (i - 1) * sz + 1, r = min(n, i * sz);
	rrep(j, l, r) {
		if(j + a[j] > r) {
			to[j] = j;
			cnt[j] = 1;
		}
		else {
			to[j] = to[j + a[j]];
			cnt[j] = cnt[j + a[j]] + 1;
		}
	}

	return;
}

pii query(int x) {
	int c = 0;
	while(to[x] + a[to[x]] <= n) {
		c += cnt[x];
		x = to[x] + a[to[x]];
	}
	return {to[x], c + cnt[x]};
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	sz = sqrt(n) + 1,  bk = ceil(n, sz);
	a.assign(n + 1, 0);
	cnt.assign(n + 1, 0);
	to.assign(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, bk) build(i);
	rep(i, 1, m) {
		int t, x, y;
		cin >> t >> x;
		if(t == 1) {
			pii ans = query(x);
			cout << ans.first << " " << ans.second << "\n";
		}
		else {
			cin >> y, a[x] = y;
			build(ceil(x, sz));
		}
	}
	return 0;
}