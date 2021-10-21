#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MOD 1000000007
#define INF 1000000000000000000
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int,int>
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
#define MAXP 10000005
int p = 1;
const int P = 32;
struct node {
	int lch, rch, sz;
}T[MAXP];
int get_new() {
	return ++p;
}
void pull(int nd) {
	T[nd].sz = T[T[nd].lch].sz + T[T[nd].rch].sz;
	return;
}
void modify(int nd, int h, int val, bitset<P> a) {
	if(h == 0) T[nd].sz += val;
	else {
		if(a[h - 1] == 0) {
			if(!T[nd].lch) T[nd].lch = get_new();
			modify(T[nd].lch, h - 1, val, a);
		}
		else {
			if(!T[nd].rch) T[nd].rch = get_new();
			modify(T[nd].rch, h - 1, val, a);
		}
		pull(nd);
	}
	return;
}
int query(int nd, int h, bitset<P> a, bitset<P> b) {
	if(!nd || h == 0) return 0;
	else {
		int ans = 0;
		if(a[h - 1] == 1) {
			if(b[h - 1] == 1) {
				ans += T[T[nd].rch].sz;
				ans += query(T[nd].lch, h - 1, a, b);
			}
			else ans += query(T[nd].rch, h - 1, a, b);
		}
		else {
			if(b[h - 1] == 1) {
				ans += T[T[nd].lch].sz;
				ans += query(T[nd].rch, h - 1, a, b);
			}
			else ans += query(T[nd].lch, h - 1, a, b);
		}
		return ans;
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int q; cin >> q;
	rep(i, 1, q) {
		int t, a, b;
		cin >> t >> a;
		if(t == 1) modify(1, P, 1, bitset<P>(a));
		else if(t == 2) modify(1, P, -1, bitset<P>(a));
		else {
			cin >> b;
			cout << query(1, P, bitset<P>(a), bitset<P>(b)) << "\n";
		}
	}
	return 0;
}
