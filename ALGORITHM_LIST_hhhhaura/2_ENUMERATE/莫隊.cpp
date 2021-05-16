#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000
#define eps (1e-9)

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
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int n, m, bk, sz, cur;
struct qry {
	int l, r, bid, id;
	bool operator<(qry b) {
		if(bid != b.bid) return bid < b.bid;
		return r < b.r;
	}
};
vector<int> ans, a, cnt;
vector<qry> qq;
void add(int x) {
	if(a[x] > n) return;
	if(cnt[a[x]] == a[x]) cur --;
	cnt[a[x]] ++;
	if(cnt[a[x]] == a[x]) cur++;
	return;
}
void minu(int x) {
	if(a[x] > n) return;
	if(cnt[a[x]] == a[x]) cur --;
	cnt[a[x]] --;
	if(cnt[a[x]] == a[x]) cur++;
	return;
}
void solve() {
	int l = 1, r = 0; cur = 0;
	cnt.assign(n + 1, 0);
	ans.assign(m + 1, 0);
	for(auto i : qq) {
		while(l > i.l) add(--l);
		while(r < i.r) add(++r);
		while(l < i.l) minu(l++);
		while(r > i.r) minu(r--);
		ans[i.id] = cur;
	}
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m;
	sz = 1000, bk = ceil(n, sz);
	a.assign(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, m) {
		int l, r; cin >> l >> r;
		qq.push_back({l, r, ceil(l, sz), i});
	}
	sort(all(qq)), solve();
	rep(i, 1, m) cout << ans[i] << "\n";
	return 0;
}
