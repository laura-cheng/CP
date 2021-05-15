#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

using namespace std;

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())
#define treap tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...); }
#else 
#define print(...) 0
#define vprint(...) 0
#endif
namespace solver {
	int n;
	struct pt {
		int x, y;
		pt operator+(pt b) { return {x + b.x, y + b.y}; }
		pt operator-(pt b) { return {x - b.x, y - b.y}; }
		int operator^(pt b) { return x * b.y - y * b.x; }
		int operator*(pt b) { return x * b.x + y * b.y; }
	};
	pt inf = {1, 1000000};
	vector<pt> a;
	void init_(int _n) {
		n = _n;
		a.assign(n, {0, 0});
	}
	bool onseg(pt &o, pt &a, pt &b) {
		return ((a - o) ^ (b - o)) == 0 && 
			((a - o) * (b - o)) <= 0;
	}
	bool ori(pt &o, pt &a, pt &b) {
		return ((a - o) ^ (b - o)) < 0;
	}
	bool banana(pt &a, pt &b, pt &c, pt &d) {
		if(!(ori(a, c, d) ^ ori(b, c, d))) return 0;
		if(!(ori(c, a, b) ^ ori(d, a, b))) return 0;
		return 1;
	}
	bool solve(pt x) {
		int cnt = 0; 
		pt y = x + inf;
		rep(i, 0, n - 2) if(onseg(x, a[i], a[i + 1])) return 1;
		if(onseg(x, a[n - 1], a[0])) return 1;
		rep(i, 0, n - 2) cnt += banana(x, y, a[i], a[i + 1]);
		cnt += banana(x, y, a[0], a[n - 1]);
		return (cnt & 1);
	}
};
using namespace solver;
namespace io {
    const int SIZE = 65536 + 10;
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
signed main() {
	int n, m; 
	read(n), read(m);
	init_(n);
	for(auto &i : a) read(i.x), read(i.y);
	int ans = 0, x, y;
	while(m --) {
		read(x), read(y);
		ans += solve({x, y});
	}
	cout << ans << "\n";
	return 0;
}

