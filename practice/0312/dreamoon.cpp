#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

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
namespace io {
    const int SIZE = 1e7 + 10;
    char inbuff[SIZE];
    char *l, *r;
    inline void init() {
        l = inbuff;
        r = inbuff + fread(inbuff, 1, SIZE, stdin);
    }
    inline char gc() {
        if (l == r) init();
        return (l != r) ? *(l++) : EOF;
    }
    void read(int &x) {
        x = 0; char ch = gc();
        while(!isdigit(ch)) ch = gc();
        while(isdigit(ch)) x = x * 10 + ch - '0', ch = gc();
    }
} using io::read;
struct segment_tree {
	int n;
	vector<int> tag, cnt;
	void init_(int _n) {
		n = _n;
		tag.assign(2 * n + 1, 0);
		cnt.assign(2 * n + 1, 0);
		build(1, n);
	}
	void build(int L, int R) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(L == R) cnt[nd] = 1;
		else {
			build(L, mid);
			build(mid + 1, R);
			cnt[nd] = (R - L + 1);
		} 
	}
	int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int nd = get(L, R), mid = (L + R) / 2;
		int lch = get(L, mid), rch = get(mid + 1, R);
		cnt[nd] = 0;
		if(!tag[lch]) cnt[nd] += cnt[lch];
		if(!tag[rch]) cnt[nd] += cnt[rch];
		return; 
	}
	void modify(int L, int R, int l, int r) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(l > R || r < L) return;
		else if(l <= L && r >= R) tag[nd] ++;
		else {
			modify(L, mid, l, r);
			modify(mid + 1, R, l, r);
			pull(L, R);
		}
	}
	int query(int L, int R, int l, int r) {
		int nd = get(L, R), mid = (L + R) / 2;
		if(l > R || r < L) return 0;
		else if(l <= L && r >= R) {
			return tag[nd] ? 0 : cnt[nd];
		}
		else {
			int ans = query(L, mid, l, r) +
				query(mid + 1, R, l, r);
			return tag[nd] ? 0 : ans;
		}
	}
};
struct AC {
	int n;
	multiset<int> s;
	segment_tree st;
	vector<int> pre, a, lst;
	void init_(int _n) {
		n = _n;
		st.init_(n);
		pre.assign(n + 1, 0);
		a.assign(n + 1, 0);
		lst.assign(n + 1, 0);
	}
	long long int solve() {
		rep(i, 1, n) {
			if(lst[a[i]] == 0) pre[i] = i;
			else pre[i] = lst[a[i]];
			lst[a[i]] = i;
			s.insert(pre[i]);
		}
		long long int ans = 0;
		rep(i, 1, n) {
			s.erase(s.find(pre[i]));
			int lb = 1;
			auto it = s.upper_bound(i);
			if(it != s.begin()) {
				it = prev(it);
				lb = *it + 1;
			} 
			st.modify(1, n, pre[i] + 1, i);
			ans += st.query(1, n, lb, i);
		}
		return ans;
	}
} ac;
signed main() {
	int t; read(t);
	while(t --) {
		int n; read(n);
		ac.init_(n);
		rep(i, 1, n) read(ac.a[i]);
		cout << ac.solve() << "\n";
	}
	return 0;
}
