#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MAXN 10000000
#define INF 1e9
#define MOD 1000000007
#define eps (1e-9)

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
struct persistent_seg {
	int n;
	vector<vector<int>> b;
	void init_(int _n, vector<int> a) {
		n = _n, p = 0;
		b.assign(n + 1, vector<int>());
		return;
	}
	void build() {
		rep(i, 1, n) 
			b[a[i]].push_back(i);
	}
	int ask(int L, int R, int x) {
		int lb = lower_bound(b[x].begin(), b[x].end(), L) - b[x].begin();
		int rb = upper_bound(b[x].begin(), b[x].end(), R) - b[x].begin() - 1;
		return rb - lb;
	}
};
random;
struct AC {
	int n, ii;
	vector<int> a, vis;
	persistent_seg st;
	void init_(int _n) {
		n = _n, ii = 0;
		a.assign(n + 1, 0);
		vis.assign(n + 1, 0);
	}
	void build() {
		st.init_(n, a);
	}
	int query(int l, int r, int k) {
		ii ++;
		int ans = INF;
		rep(i, 1, 10) {
			int id = l + rnd() % (r - l + 1);
			if(vis[a[id]] == ii) continue;
			vis[a[id]] = ii;
			int cnt = st.ask(l, r, a[id]);
			if(cnt * k > r - l + 1) ans = min(ans, a[id]);
		}		
		if(ans == INF) return -1;
		else return ans;
	}
} ac;
signed main() {
	int n, q; read(n), read(q);
	ac.init_(n);
	rep(i, 1, n) read(ac.a[i]);
	ac.build();
	rep(i, 1, q) {
		int l, r, k;
		read(l), read(r), read(k);
		printf("%d\n", ac.query(l, r, k));
	}	
	
	return 0;
}
