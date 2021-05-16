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
int n = 50, m, s;
vector<int> es, deg, ans, vis;
vector<vector<int>> mp;
void init_() {
    es.clear(), ans.clear();
    deg.assign(n + 1, 0);
    mp.assign(n + 1, vector<int>());
    return;
}
void dfs(int x, int par) {
    for(auto i : mp[x]) {
        if(i == par || vis[i]) continue;
        vis[i] = 1, dfs(es[i] ^ x, i);
        ans.push_back(i);
    }
    return;
}
bool solve() {
    rrep(i, 1, n) {
        if(deg[i] & 1) return false;
        else if(deg[i]) s = i;
    }
    vis.assign(m, 0);
    dfs(s, -1);
    if(ans.size() == m) return true;
    else return false;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t; cin >> t;
    rep(tt, 1, t) {
        cin >> m, init_();
        rep(i, 1, m) {
            int x, y; cin >> x >> y;
            es.push_back(x ^ y);
            mp[x].push_back(i - 1);
            mp[y].push_back(i - 1);
            deg[x] ++, deg[y] ++;
        }
        bool yes = solve();
        cout << "Case #" << tt << "\n";
        if(yes) {
            for(auto i : ans) {
                cout << s << " " << (es[i] ^ s) << "\n";
                s = es[i] ^ s;
            }
        }
        else cout << "some beads may be lost\n";
        cout << "\n";
    }
    return 0;
}
