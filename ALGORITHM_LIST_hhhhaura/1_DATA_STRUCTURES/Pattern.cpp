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

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now::time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() {cerr << endl;}
template<class T1, class ...T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
#define get(L, R) ((L + R) | (L != R))
int n;
struct node {
	int tag, cnt[3]; 
	node() {
		tag = 0;
		cnt[0] = cnt[1] = cnt[2] = 0;
	}
};
vector<int> vis, out, in, deg;
vector<node> seg;
vector<vector<int>> mp;
void init_() {
	mp.assign(n + 1, vector<int>());
	vis.assign(n, 0);
	out.assign(n + 1, 0);
	seg.assign(2 * n + 1, node());
	in.assign(n + 1, 0);
	deg.assign(n + 1, 0);
	return;
}
int get_two(int nd) {
	if(seg[nd].tag > 2) return 0;
	else return seg[nd].cnt[2 - seg[nd].tag];
}
void pull(int L, int R) {
	int nd = get(L , R), mid = (L + R) / 2;
	int lch = get(L, mid), rch = get(mid + 1, R);
	rep(i, 0, 2) {
		seg[nd].cnt[i] = (
			(seg[lch].tag > i ? 0 : seg[lch].cnt[i - seg[lch].tag]) + 
			(seg[rch].tag > i ? 0 : seg[rch].cnt[i - seg[rch].tag])
		);
	}
	return;
}
void build(int L, int R) {
	int mid = (L  + R) / 2, nd = get(L, R);
	if(L == R) seg[nd].cnt[0] = 1;
	else {
		build(L, mid);
		build(mid + 1, R);
		pull(L, R);
	}
}
void modify(int L, int R, int l, int r, int val) {
	int nd = get(L, R), mid = (L + R) / 2;
	int lch = get(L, mid), rch = get(mid + 1, R);
	if(l > R || r < L || l > r) return;
	else if(l <= L && r >= R) {
		seg[nd].tag += val;
	}
	else {
		modify(L, mid, l, r, val);
		modify(mid + 1, R, l, r, val);
		pull(L, R);
	} 
	return;
}
int solve() {
	int ans = 0;
	build(1, n);
	rep(i, 1, n) {
		sort(all(mp[i]));
		mp[i].push_back(n + 1);
		in[i] = max(i, mp[i][0]);
		out[i] = 1, in[i] = 0;
		modify(1, n, max(i, mp[i][in[i]]), mp[i][out[i]] - 1, 1);
		modify(1, n, i, mp[i][in[i]] - 1, 1e9);
	}
	rep(i, 1, n) {
		ans += get_two(get(1, n));
		modify(1, n, max(i, mp[i][in[i]]), mp[i][out[i]] - 1, -1);
		modify(1, n, i, mp[i][in[i]] - 1, -1e9);
		for(auto j : mp[i]) {
			if(j < i || j == n + 1) continue;
			if(i == mp[j][out[j] - 1]) {
				modify(1, n, max(j, mp[j][in[j]]), mp[j][out[j]] - 1, -1);
				modify(1, n, j, mp[j][in[j]] - 1, -1e9);
				if(in[j] + 1 < mp[j].size()) in[j] ++;
				if(out[j] + 1 < mp[j].size()) out[j] ++;
				modify(1, n, max(j, mp[j][in[j]]), mp[j][out[j]] - 1, 1);
				modify(1, n, j, mp[j][in[j]] - 1, 1e9);
			}
		}
		
	}
	return ans + n;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n, init_();
	rep(i, 1, n - 1) {
		int a, b;
		cin >> a >> b;
		mp[b].push_back(a);
		mp[a].push_back(b);
	}
	cout << solve() << "\n";
	return 0;
}
