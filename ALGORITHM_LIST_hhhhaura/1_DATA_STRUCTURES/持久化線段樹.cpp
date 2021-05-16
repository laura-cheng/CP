#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i, a, b) for(int i = a; i <= b; i++) 
#define all(x) x.begin(), x.end()
#define MAXP 5000000
using namespace std;
int n, m, p = 0, mx;
struct node {
	int lch, rch, val;
	node() {
		lch = rch = val = 0;
	}
};
vector<node> seg(MAXP, node());
vector<int> a, v, T;
int get_new() {return ++p;}
void pull(int nd) {
	seg[nd].val = seg[seg[nd].lch].val + seg[seg[nd].rch].val;
	return;
}
int get_copy(int nd) {
	++p;
	seg[p].lch = seg[nd].lch;
	seg[p].rch = seg[nd].rch;
	seg[p].val = seg[nd].val;
	return p;
}
void modify(int pre, int cur, int L, int R, int id, int val) {
	if(L == R) {
		seg[cur].val += val;
	}
	else {
		int mid = (L + R) / 2;
		if(id <= mid) {
			if(!seg[pre].lch) seg[cur].lch = get_new();
			else seg[cur].lch = get_copy(seg[pre].lch);
			modify(seg[pre].lch, seg[cur].lch, L, mid, id, val);
		}
		else {
			if(!seg[pre].rch) seg[cur].rch = get_new();
			else seg[cur].rch = get_copy(seg[pre].rch);
			modify(seg[pre].rch, seg[cur].rch, mid + 1, R, id, val);
		}
		pull(cur);
	}
}
int build(int L, int R) {
	if(L == R) return get_new();
	else {
		int mid = (L + R) / 2, nd = get_new();
		seg[nd].lch = build(L, mid);
		seg[nd].rch = build(mid + 1, R);
		return nd;
	} 
}
void init() {
	rep(i, 1, n) v.push_back(a[i]);
	sort(all(v)), v.resize(unique(all(v)) - v.begin());
	mx = v.size();
	rep(i, 1, n) {
		a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1; 
	}
	T.assign(n + 1, 0);
	T[0] = build(1, mx);
	rep(i, 1, n) {
		T[i] = get_copy(T[i - 1]);
		modify(T[i - 1], T[i], 1, mx, a[i], 1ll);
	}
	return;
}
int query(int lt, int rt, int L, int R, int k) {
	if(L == R) return v[L - 1];
	else {
		int mid = (L + R) / 2;
		int ll = seg[lt].lch, rr = seg[rt].lch;
		int vv = seg[rr].val - seg[ll].val;
		if(vv >= k) return query(seg[lt].lch, seg[rt].lch, L, mid, k);
		else return query(seg[lt].rch, seg[rt].rch, mid + 1, R, k - vv); 
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m, a.assign(n + 1, 0);
	rep(i, 1, n) cin >> a[i];
	init();
	rep(i, 1, m) {
		int l, r, k;
		cin >> l >> r >> k;
		cout << query(T[l - 1], T[r], 1, mx, k) << "\n";
	}
	return 0;
}
