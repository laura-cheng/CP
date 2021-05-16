
//#define wiwihorz
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
const int N = 14;
int n, m, P, p[N][N];
int mp[100][100], id[N], cost[N];
int dp[1 << N][N];
void init_() {
    rep(i, 0, n) rep(j, 0, n) {
        mp[i][j] = INF;
    }
    rep(i, 0, n) mp[i][i] = 0;
}
void build() {
    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) {
        mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
    }
    rep(i, 0, P) rep(j, 0, P) {
        p[i][j] = -mp[id[i]][id[j]];
    }
    return;
}
int solve() {
    P ++;
    rep(i, 0, (1 << P) - 1) rep(j, 0, P - 1) {
        dp[i][j] = -INF;
    }
    dp[1][0] = 0;
    int ans = 0;
    rep(i, 0, (1 << P) - 1) {
        rep(j, 0, P - 1) if((i >> j) & 1) {
            int mask = i ^ (1 << j);
            rep(k, 0, P - 1) if((mask >> k) & 1) {
                dp[i][j] = max(
                    dp[i][j],
                    dp[mask][k] + p[j][k] + cost[j]
                );
            }
            ans = max(ans, dp[i][j] - mp[0][id[j]]);

        }
    }
    return ans;
}
signed main() {
    int t; scanf("%lld", &t);
    while(t--) {
        scanf("%lld %lld", &n, &m);
        init_();
        rep(i, 1, m) {
            int a, b, c1, c2;
            scanf("%lld %lld", &a, &b);
            scanf("%lld.%lld", &c1, &c2);
            mp[a][b] = min(mp[a][b], c1 * 100 + c2);
            mp[b][a] = min(mp[b][a], c1 * 100 + c2);
        }
        scanf("%lld", &P);
        rep(i, 1, P) {
            int c1, c2;
            scanf("%lld %lld.%lld", &id[i], &c1, &c2);
            cost[i] = c1 * 100 + c2;
        }
        build();
        int ans = solve();
        if(ans <= 0) printf("Don't leave the house\n");
        else printf("Daniel can save $%lld.%.2lld\n", ans / 100, ans % 100);
    }
    return 0;
}
