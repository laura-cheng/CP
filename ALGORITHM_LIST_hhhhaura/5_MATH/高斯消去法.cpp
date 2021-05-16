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
//#define MOD 1000000007
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
int MOD, a[200][200], n;
int pow_(int a, int times) {
    int ans = 1;
    for(;times > 0; times >>= 1, a = a * a % MOD) {
        if(times & 1) ans = ans * a % MOD;
    }
    return ans;
}
void sswap(int aa, int bb) {
    rep(i, 1, n + 1) {
        swap(a[aa][i], a[bb][i]);
    }
    return;
}
void put() {
    rep(i, 1, n) {
        rep(j, 1, n + 1) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
    return ;
}
int ddiv(int a, int b) {
    return a * pow_(b, MOD - 2) % MOD;
}
void solve() {
    rep(i, 1, n) {
        int piv = i;
        while(!a[piv][i]) piv ++;
        sswap(i, piv);
        rep(j, 1, n + 1) if(j != i) {
            a[i][j] = ddiv(a[i][j], a[i][i]);
        }
        a[i][i] = 1;
        rep(j, 1, n) if(j != i) {
            int mul = a[j][i];
            rep(k, 1, n + 1) {
                a[j][k] -= mul * a[i][k];
                a[j][k] %= MOD;
            }
        }
//        put();
    }
    rep(i, 1, n) rep(j, 1, n + 1) {
        a[i][j] = (a[i][j] % MOD + MOD) % MOD;
    }
    return;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> MOD;
    rep(i, 1, n) cin >> a[i][n + 1];
    rep(i, 1, n) rep(j, 1, n) {
        cin >> a[j][i];
    }
    solve();
    rep(i, 1, n) {
        cout << a[i][n + 1] << " \n"[i == n];
    }
    return 0;
}
