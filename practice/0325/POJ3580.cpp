#include <iostream>
#include <algorithm>
#include <string>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define INF 2147483647
#define pii pair<int, int>
#define ll int 
#define MAXP 200005
using namespace std;
struct seg {
	int l, mid, r;
	seg(int a, int b, int c) {
		l = a, mid = b, r = c;
	}
};
int lch[MAXP], rch[MAXP], sz[MAXP], pri[MAXP], rev[MAXP];
ll mn[MAXP], tag[MAXP], val[MAXP];
int p, root;
void init_() {
	p = 0, root = 0;
	val[0] = mn[0] = INF;
}
int get_new(ll v = INF) {
	++p, sz[p] = 1;
	val[p] = v, mn[p] = v;
	pri[p] = rand();
	return p;
}
void pull(int nd) {
	int l = lch[nd], r = rch[nd];
	sz[nd] = 1 + sz[l] + sz[r];
	mn[nd] = min(val[nd], mn[l] + tag[l]);
	mn[nd] = min(mn[nd], mn[r] + tag[r]);
}
void push(int nd) {
	int l = lch[nd], r = rch[nd];
	if(tag[nd]) {
		if(l) tag[l] += tag[nd];
		if(r) tag[r] += tag[nd];
		val[nd] += tag[nd];
		mn[nd] += tag[nd];
		tag[nd] = 0;
	}
	if(rev[nd]) {
		swap(lch[nd], rch[nd]);
		rev[l] ^= 1;
		rev[r] ^= 1;
		rev[nd] = 0;
	}
	return;
}
int merge(int pre, int suf) {
	if(!pre) return suf;
	if(!suf) return pre;
	push(pre), push(suf);
	if(pri[pre] > pri[suf]) {
		rch[pre] = merge(rch[pre], suf);
		pull(pre);
		return pre;
	}
	else {
		lch[suf] = merge(pre, lch[suf]);
		pull(suf);
		return suf;
	}
}
pii split(int nd, int k) {
	if(!nd) return pii(0, 0);
	push(nd);
	if(sz[lch[nd]] >= k) {
		pii p = split(lch[nd], k);
		lch[nd] = p.second;
		pull(nd);
		return pii(p.first, nd);
	}
	else {
		pii p = split(rch[nd], k - 1 - sz[lch[nd]]);
		rch[nd] = p.first;
		pull(nd);
		return pii(nd, p.second);
	}
}
seg get_seg(int L, int R) {
	pii p; int a;
	p = split(root, L - 1);
	a = p.first;
	p = split(p.second, R - L + 1);
	return seg(a, p.first, p.second);
}
void add(int L, int R, ll k) {
	seg a = get_seg(L, R);
	tag[a.mid] += k;
	root = merge(merge(a.l, a.mid), a.r);
}
void rreverse(int L, int R) {
	seg a = get_seg(L, R);
	rev[a.mid] ^= 1;
	root = merge(merge(a.l, a.mid), a.r);
}
void revolve(int L, int R, ll k) {
	seg a = get_seg(L, R);
	int len = (R - L + 1), x = ((len - k) % len + len) % len;
	pii p = split(a.mid, x);
	root = merge(merge(a.l, p.second), merge(p.first, a.r));
}
void insert(int x, int k) {
	pii p = split(root, x);
	int cur = get_new(k);
	root = merge(merge(p.first, cur), p.second);
}
void erase(int x) {
	seg a = get_seg(x, x);
	root = merge(a.l, a.r);
}

void trav(int x) {
	if(!x) return;
	push(x);
	if(lch[x]) trav(lch[x]);
	cerr << val[x] << " ";
	if(rch[x]) trav(rch[x]);
	return;
}
ll query(int L, int R) {
	seg a = get_seg(L, R);
	ll ans = mn[a.mid] + tag[a.mid];
	root = merge(merge(a.l, a.mid), a.r);
	return ans;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m; srand(7122); 
	cin >> n, init_();
	rep(i, 1, n) {
		ll x; cin >> x;
		int p = get_new(x);
		root = merge(root, p);
	}
	cin >> m;
	rep(i, 1, m) {
		string op; ll a, b, c;
		cin >> op;
		if(op[0] == 'M') {
			cin >> a >> b;
			cout << query(a, b) << "\n";
		}
		else if(op[0] == 'A') {
			cin >> a >> b >> c;
			add(a, b, c);
		}
		else if(op[0] == 'D') {
			cin >> a;
			erase(a);
		}
		else if(op[0] == 'I') {
			cin >> a >> b;
			insert(a, b);
		}
		else if(op[3] == 'E') {
			cin >> a >> b;
			rreverse(a, b);
		}
		else {
			cin >> a >> b >> c;
			revolve(a, b, c);
		}
		
		
	}
	
	return 0;
}
