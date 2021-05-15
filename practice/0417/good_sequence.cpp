#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define rrep(i, a, b) for(int i = b; i >= a; --i)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

//#define int long long int
#define ll long long 
#define lld long double
#define pii pair<int ,int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L; }
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif

namespace seg {
	int n;
	signed cnt[MAXN][3];
	signed tag[MAXN];
	inline int get(int L, int R) {
		return (L + R) | (L != R);
	}
	void pull(int L, int R) {
		int mid = (L + R) / 2, nd = get(L, R);
		int lch = get(L, mid), rch = get(mid + 1, R);
		rep(i, 0, 2) {
			cnt[nd][i] = 0;
			if(i - tag[lch] >= 0) cnt[nd][i] += cnt[lch][i - tag[lch]];
			if(i - tag[rch] >= 0) cnt[nd][i] += cnt[rch][i - tag[rch]];
		}
		return;
	}
	void build(int L, int R) {
		signed mid = (L + R) / 2, nd = get(L, R);
		if(L == R) cnt[nd][0] = 1, tag[nd] = 0;
		else {
			build(L, mid);
			build(mid + 1, R);
			pull(L, R);
		}
	}
	void init_(int _n) {
		n = _n;
		build(1, n);
	}
	void modify(int L, int R, int l, int r, int v) {
		int mid = (L + R) / 2, nd = get(L, R);
		if(l > R || r < L) return;
		else if(l <= L && r >= R) tag[nd] += v;
		else {
			modify(L, mid, l, r, v);
			modify(mid + 1, R, l, r, v);
			pull(L, R);
		}	
		return;
	}
	ll ask() {
		int nd = get(1, n);
		if(tag[nd] > 2) return 0;
		else return cnt[nd][2 - tag[nd]];
	}
};
namespace solver {
	int n;
	int a[MAXN], b[MAXN], vis[MAXN], L[MAXN], R[MAXN];
	void init_(int _n) {
		n = _n;
		rep(i, 1, n + 1) {
			vis[i] = 0;
			L[i] = n + 1;
			R[i] = n + 1; 
		}
		seg::init_(n);
	} 
	ll solve() {
		rep(i, 1, n) b[a[i]] = i;
		rep(i, 1, n) {
			vis[b[i]] = 1;
			if(L[b[i]] == n + 1) L[b[i]] = i;
			else R[b[i]] = i;
			
			if(L[b[i] + 1] == n + 1) L[b[i] + 1] = i;
			else R[b[i] + 1] = i;
		}
		rep(i, 1, n + 1) seg::modify(1, n, L[i], R[i] - 1, 1);
		ll ans = 0;
		
		rep(i, 1, n) {
			int id = b[i];
			ans += seg::ask();
			seg::modify(1, n, L[id], R[id] - 1, -1);
			seg::modify(1, n, L[id + 1], R[id + 1] - 1, -1);
			L[id] = R[id], R[id] = n + 1;
			L[id + 1] = R[id + 1], R[id + 1] = n + 1;
			seg::modify(1, n, L[id], R[id] - 1, 1);
			seg::modify(1, n, L[id + 1], R[id + 1] - 1, 1);
		}
		return ans;
	}
};
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
using namespace solver;
signed main() {
	int t; read(t);
	while(t --) {
		int n; read(n);
		init_(n);
		rep(i ,1, n) read(a[i]);
		printf("%lld\n", solve());
	}

	return 0;
}
