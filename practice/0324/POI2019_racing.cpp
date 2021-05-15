#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random t19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

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
struct segment_tree {
	int n;
	vector<int> ori, val, mx;
	vector<int> a, b, tag;
	void init_(int _n, vector<int> _a, vector<int> _b) {
		n = _n;
		ori.assign(2 * n + 1, 0);
		val.assign(2 * n + 1, 0);
		tag.assign(2 * n + 1, 0);
		a = _a, b = _b;
		build(1, n);
	}
	void build(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(L == R) val[nd] = b[L], ori[nd] = a[L];
		else {
			build(L, mid);
			build(mid + 1, R);
			pull(L, R);
		}
		
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void push(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		tag[lch] += tag[nd], tag[rch] += tag[nd];
		ori[nd] += tag[nd], val[nd] += tag[nd];
		tag[nd] = 0;
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int rch = get(mid + 1, R), lch = get(L, mid);
		val[nd] = max(val[rch] + tag[rch], val[lch] + tag[lch]);
		ori[nd] = max(ori[rch] + tag[rch], ori[lch] + tag[lch]);
	}
	void modify(int L, int R, int l, int r, int val) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(l > R || r < L) return;
		if(L != R) push(L, R);
		if(l <= L && r >= R) tag[nd] += val;
		else {
			modify(L, mid, l, r, val);
			modify(mid + 1, R, l, r, val);
			pull(L, R);
		}
	}
	int query_ori(int L, int R, int v) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		if(L == R && ori[nd] + tag[nd] <= v) return n + 1;
		else if(L == R) {return L;}
		push(L, R);
		if(ori[lch] + tag[lch] > v) return query_ori(L, mid, v);
		else return query_ori(mid + 1, R, v);	
	}
	void bonus(int x, int y) {
		int id = query_ori(1, n, x - 1);
		modify(1, n, id, n, y);
	}
	void penalty(int x, int y) {
		int id = query_ori(1, n, x) - 1;
		modify(1, n, 1, id, -y);
	}
	int ask() {
		int cur = val[get(1, n)] + tag[get(1, n)];
		int id = query_ori(1, n, cur - n - 1);
		return n - id + 1;
	}
};
namespace SOLVE {
	int n;
	vector<int> a, b;
	segment_tree st;
	void init_(int _n) {
		n = _n;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
	}
	void build() {
		sort(all(a));
		int pre = 1, cur = n;
		rep(i, 1, n) {
			if(i == n || a[i + 1] != a[pre]) {
				rrep(j, pre, i) {
					b[j] = a[j] + cur, cur --;
				}
				pre = i + 1;
			}
		}
		st.init_(n, a, b);
	}
	void B(int x, int y) { st.bonus(x, y); }
	void K(int x, int y) { st.penalty(x, y); }
	int Z() { return st.ask(); }
};
using namespace SOLVE; 
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, q; cin >> n >> q;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	build();
	rep(i, 1, q) {
		char op; cin >> op;
		int x, y;
		if(op == 'B') {
			cin >> x >> y;
			B(x, y);
		}
		else if(op == 'K') {
			cin >> x >> y;
			K(x, y);
		}
		else cout << Z() << "\n";
	}
	
	return 0;
}
