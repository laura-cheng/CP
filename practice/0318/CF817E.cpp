#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
const int H = 32;
const int P = 10000000;
int sz[P], lch[P], rch[P];
struct TRIE {
	int p, root;
	void init_() {
		p = 1, root = 1;

	}
	int get_new() {
		return ++ p;
	}
	void pull(int nd) {
		sz[nd] = sz[lch[nd]] + sz[rch[nd]];
		return;
	}
	void modify(int nd, int h, bitset<H> a, int v) {
		if(h == 0) sz[nd] += v;
		else {
			if(a[h - 1] == 0) {
				if(!lch[nd]) lch[nd] = get_new();
				modify(lch[nd], h - 1, a, v);
			}
			else {
				if(!rch[nd]) rch[nd] = get_new();
				modify(rch[nd], h - 1, a, v);
			}
			pull(nd);
		}
	}
	int query(int nd, int h, bitset<H> a, bitset<H> b) {
		if(h == 0 || !nd) return sz[nd];
		else {
			int ans = 0;
			if(b[h - 1]) {
				if(a[h - 1]) {
					ans += sz[rch[nd]];
					ans += query(lch[nd], h - 1, a, b);
				}
				else {
					ans += sz[lch[nd]];
					ans += query(rch[nd], h - 1, a, b);
				}
			}
			else {
				if(a[h - 1]) ans += query(rch[nd], h - 1, a, b);
				else ans += query(lch[nd], h - 1, a, b);
			}
			return ans;
		}
	}
	void change(int val, int tp) {
		if(tp == 1) modify(root, H, bitset<H>(val), 1);
		else modify(root, H, bitset<H>(val), -1);
	}
	int ask(int p, int l) {
		return query(root, H, bitset<H>(p), bitset<H>(l));
	}
} trie;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	trie.init_();
	int q; cin >> q;
	while(q--) {
		int tp; cin >> tp;
		if(tp == 1 || tp == 2) {
			int val; cin >> val;
			trie.change(val, tp);
		}
		else {
			int p, l; cin >> p >> l;
			cout << trie.ask(p, l) << "\n";
		}
	}
	return 0;
}


