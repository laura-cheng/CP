#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a;i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MAXN 1000005
#define MOD 1000000007
#define eps (1e-9)

//#define int long long int
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
#define lowbit(x) (x & -x)
struct BIT {
    int n;
    vector<int> v;
    void init_(int _n) {
        n = _n;
        v.assign(n + 1, 0);
    }
    void modify(int x, int val) {
        for(int i = x; i <= n; i+= lowbit(i)) {
            v[i] += val;
        }
    }
    int query(int x) {
        int ans = 0;
        for(int i = x; i > 0; i -= lowbit(i)) {
            ans += v[i];
        }
        return ans;
    }
    void add(int l, int r, int val) {
        modify(l, val);
        modify(r + 1, -val);
    }
} bit;
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n; cin >> n;
    set<int> s;
    s.insert(n + 1), bit.init_(n);
    rep(i, 1, n) {
        int l, r; cin >> l >> r;
        l ++, r ++;
        int cur = bit.query(r) + 1;
        s.insert(l);
        auto rr = s.upper_bound(r);
        bit.add(l, *rr - 1, 1);
        for(auto it = rr; next(it) != s.end(); ) {
            int val = bit.query(*it);
            if(val < cur) {
                bit.add(*it, *next(it) - 1, cur - val);
                auto temp = it;
                it = next(it);
                s.erase(temp);
            }
            else break;
        }
    }
    cout << bit.query(n) << "\n";
    return 0;
}
