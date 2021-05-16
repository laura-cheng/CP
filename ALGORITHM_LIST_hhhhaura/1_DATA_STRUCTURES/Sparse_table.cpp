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

#define int long long int
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
int n, lg;
vector<int> a;
vector<vector<int>> st;
void build() {
    lg = 32 - __builtin_clz(n);
    st.assign(lg + 1, vector<int>(n + 1, -INF));
    rep(i, 1, n) st[0][i] = a[i];
    rep(i, 1, lg) rep(j, 1, n) {
        st[i][j] =
        max(
            st[i - 1][j],
            st[i - 1][j + (1 << (i - 1))]
        );
    }
    return;
}
int query(int L, int R) {
    int x = 31 - __builtin_clz(R - L + 1);
    return max(st[x][L], st[x][R - (1 << x) + 1]);
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    a.assign(n + 1, 0);
    rep(i, 1, n) cin >> a[i];
    build();
    int m; cin >> m;
    rep(i, 1, m) {
        int l, r; cin >> l >> r;
        if(l > r) swap(l, r);
        cout << query(l, r) << "\n";
    }
    return 0;
}

