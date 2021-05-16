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
int n, m;
struct edge {
    int from, to, cost;
};
vector<int> dis;
vector<edge> es;
int solve(int s, int t) {
    int cnt = 0;
    dis[s] = 0;
    rep(i, 1, n) {
        bool yes = 0;
        for(auto j : es) {
            int v = dis[j.from] + j.cost;
            if(v < dis[j.to]) {
                yes = 1;
                dis[j.to] = v;
            }
        }
        if(!yes) break;
        else cnt ++;
    }
    if(n == cnt || dis[t] == INF) return -1;
    else return dis[t];
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t; cin >> t;
    rep(tt, 1, t) {
        int S, T;
        cin >> n >> m >> S >> T;
        dis.assign(n + 1, INF);
        es.clear();
        S ++, T ++;
        rep(i, 1, m) {
            int a, b, c;
            cin >> a >> b >> c;
            a ++, b ++;
            es.push_back({a, b, c});
            es.push_back({b, a, c});
        }
        int ans = solve(S, T);
        if(ans == -1) cout << "Case #" << tt << ": unreachable\n";
        else cout << "Case #" << tt << ": " << ans << "\n";
    }
    return 0;
}

