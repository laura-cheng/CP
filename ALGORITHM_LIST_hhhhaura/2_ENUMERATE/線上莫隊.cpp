#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R],++L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else
#define print(...) 0
#define vprint(...) 0
#endif
int n, q;
struct query {
	int l, r, lid, rid, id;
	bool operator<(query b) {
		if(lid != b.lid) return lid < b.lid;
		if(rid != b.rid) return rid < b.rid;
		return id < b.id;
	}
};
struct event {
	int pre, cur, x, id;
};
int l, r, sz , cur;
vector<int> temp, a, cnt, num, v, ans;
vector<event> evt;
vector<query> qq;
void add(int x) {
	cnt[num[a[x]]] --;
	num[a[x]] ++;
	cnt[num[a[x]]] ++;
	return;
}
void minu(int x) {
	cnt[num[a[x]]] --;
	num[a[x]] --;
	cnt[num[a[x]]] ++;
	return;
}
void forw(int x) {
	if(l <= evt[x].x && r >= evt[x].x)  minu(evt[x].x);
	a[evt[x].x] = evt[x].cur;
	if(l <= evt[x].x && r >= evt[x].x) add(evt[x].x);
	return;
}
void back(int x) {
	if(l <= evt[x].x && r >= evt[x].x) minu(evt[x].x);
	a[evt[x].x] = evt[x].pre;
	if(l <= evt[x].x && r >= evt[x].x) add(evt[x].x);
	return;
}
void solve() {
	sort(all(qq));
	l = 1, r = 0, cur = -1;
	for(auto i : qq) {

		while(l > i.l) add(--l);
		while(r < i.r) add(++r);
		while(l < i.l) minu(l++);
		while(r > i.r) minu(r--);
		while(cur + 1 < evt.size() 
			&& i.id >= evt[cur + 1].id) forw(++cur);
		while(cur >= 0 && i.id < evt[cur].id) 
			back(cur--);
		int aa = 1;
		while(cnt[aa]) aa ++;
		ans[i.id] = aa;
	}
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> q, sz = 3500;
	a.assign(n + 1, 0), temp.assign(n + 1, 0);
	ans.assign(q + 1, 0), num.assign(n + q + 1, 0);
	cnt.assign(n + 1, 0);
	rep(i, 1, n) {
		cin >> a[i];
		v.push_back(a[i]);
	}
	temp = a;
	rep(i, 1, q) {
		int t, aa, bb;
		cin >> t >> aa >> bb;
		if(t == 1) {	
			qq.push_back({aa, bb, aa / sz, bb / sz, i});
		}
		else {
			evt.push_back({temp[aa], bb, aa, i});
			temp[aa] = bb;
			v.push_back(bb);
		}
	}
	sort(all(v)), v.resize(unique(all(v)) - v.begin());
	rep(i, 1, n) {
		a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
	}
	for(auto &i : evt) {
		i.pre = lower_bound(v.begin(), v.end(), i.pre) - v.begin() + 1;
		i.cur = lower_bound(v.begin(), v.end(), i.cur) - v.begin() + 1;
	}
	solve();
	rep(i, 1, q) {
		if(ans[i]) cout << ans[i] << "\n";
	}
	return 0;
}
