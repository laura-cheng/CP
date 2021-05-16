#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MOD 1000000007
#define MAXN 1000005
#define INF 1000000000000000000
#define eps (1e-9)

//#define int long long int
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
#define get(L, R) ((L + R) | (L != R))
int n, mx;
vector<int> seg, tag;
void pull(int L, int R) {
	int nd = get(L, R), mid = (L + R) / 2;
	int lch = get(L, mid), rch = get(mid + 1, R);
	seg[nd] = max({
		seg[lch] + tag[lch],
		seg[rch] + tag[rch]
	});
	return;
}
void modify(int L, int R, int l, int r, int val) {
	int nd = get(L, R), mid = (L + R) / 2;
	if(l > R || r < L) return;
	if(l <= L && r >= R) tag[nd] += val;
	else {
		modify(L, mid, l, r, val);
		modify(mid + 1, R, l, r, val);
		pull(L, R);
	}
	return;
}
struct ln {
	int x, u, d, w;
	bool operator<(ln b) {
		return x < b.x;
	}
};
vector<ln> a;
vector<int> v, x1, yy1, x2, y2, w;
void build() {
	sort(all(v)), v.resize(unique(all(v)) - v.begin());
	seg.assign(2 * v.size() + 1, 0);
	tag.assign(2 * v.size() + 1, 0);
	mx = v.size();
	rep(i, 1, n) {
		yy1[i] = lower_bound(v.begin(), v.end(), yy1[i]) - v.begin() + 1;
		y2[i] = lower_bound(v.begin(), v.end(), y2[i]) - v.begin() + 1;
		modify(1, mx, yy1[i], y2[i], w[i]); 
	}
	for(auto &i : a) {
		i.u = lower_bound(v.begin(), v.end(), i.u) - v.begin() + 1;
		i.d = lower_bound(v.begin(), v.end(), i.d) - v.begin() + 1; 
	}
	return;
}
int solve() {
	sort(all(a));
	int ans = 0, cur = 0, pre = 0;
	for(auto i : a) {
		if(i.x != pre) {
			ans = max(
				ans,
				cur + seg[get(1, mx)] + tag[get(1, mx)]
			);
			pre = i.x;
		}
		modify(1, mx, i.u, i.d, -i.w);
		cur += i.w;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	yy1.assign(n + 1, 0);
	y2.assign(n + 1, 0);
	w.assign(n + 1, 0);
	rep(i, 1, n) {
		int x1, x2;
		cin >> x1 >> yy1[i];
		cin >> x2 >> y2[i];
		cin >> w[i];
		v.push_back(yy1[i]);
		v.push_back(y2[i]);
		a.push_back({x1, yy1[i], y2[i], w[i]});
		a.push_back({x2 + 1, yy1[i], y2[i], -w[i]});
	}
	build();
	cout << solve() << "\n";
	return 0;
}

