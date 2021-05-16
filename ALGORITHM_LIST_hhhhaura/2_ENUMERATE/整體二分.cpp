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
#define lowbit(x) (x & -x)
int n, t, q;
struct evt {
	int tp, l, r, k, c, v, id;
};
vector<int> bit, v, cur;
vector<evt> es;
vector<pii> ans;
int query(int x) {
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i)) {
		ans += bit[i];
	}
	return ans;
}
void modify(int x, int val) {
	for(int i = x; i <= n; i += lowbit(i)) {
		bit[i] += val;
	}
	return;
}
void do_things(int mid, vector<evt> &a, vector<evt> &l, vector<evt> &r) {
	vector<pii> ops;
	for(auto i : a) {
		if(i.tp == 1) {
			int vv = query(i.r) - query(i.l - 1);
			if(i.k <= vv) l.push_back(i);
			else i.k -= vv, r.push_back(i);
		}
		else {
			if(i.v > mid) r.push_back(i);
			else {
				modify(i.c, i.id);
				ops.push_back({i.c, i.id});
				l.push_back(i);
			}
		}
	}
	for(auto i : ops) {
		modify(i.first, -i.second);
	}
	return;
}
void tobs(int l, int r, vector<evt> &a) {
	if(l == r) {
		for(auto i : a) {
			if(i.tp == 1) 
				ans.push_back({i.id, v[l - 1]});
		}
		return;
	}
	int mid = (l + r) / 2;
	vector<evt> L, R;
	do_things(mid, a, L, R);
	tobs(l, mid, L);
	tobs(mid + 1, r, R);
	a.clear(), L.clear(), R.clear();
	return;
}
void parse() {
	rep(i, 1, n) {
		cin >> cur[i];
		es.push_back({2, 0, 0, 0, i, cur[i], 1});
		v.push_back(cur[i]);
	}
	int t, a, b, c;
	rep(i, 1, q) {
		cin >> t;
		if(t == 1) {
			cin >> a >> b >> c;
			es.push_back({1, a, b, c, 0, 0, i});
		}
		else if(t == 2) {
			cin >> a >> b;
			es.push_back({2, 0, 0, 0, a, cur[a], -1});
			cur[a] = b;
			es.push_back({2, 0, 0, 0, a, cur[a], 1});
			v.push_back(b);
		}
		else {
			cin >> a >> b;
			ans.push_back({i, 7122});
		}
	}
	return;
}
void discrete() {
	sort(all(v)), v.resize(unique(all(v)) - v.begin());
	for(auto &i : es) {
		i.v = lower_bound(v.begin(), v.end(), i.v) - v.begin() + 1;
	}
	return;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> t;
	while(t--) {
		cin >> n >> q;
		ans.clear();
		es.clear();
		v.clear();
		cur.assign(n + 1, 0);
		bit.assign(n + 1, 0);
		parse();
		discrete();
		tobs(1, v.size(), es);
		sort(all(ans));
		for(auto i : ans) {
			cout << i.second << "\n";
		}
	}
	return 0;
}
