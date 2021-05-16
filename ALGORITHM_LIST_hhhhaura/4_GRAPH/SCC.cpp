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
int n, m, timestamp, ii, sccid;
vector<int> D, L, instack, pre, id, deg;
vector<vector<int>> mp;
void init_() {
    D.assign(n + 1, 0);
    L.assign(n + 1, 0);
    instack.assign(n + 1, 0);
    pre.assign(n + 1, 0);
    id.assign(n + 1, 0);
    deg.assign(n + 1, 0);
    mp.assign(n + 1, vector<int>());
    timestamp = ii = sccid = 0;
    return;
}
void dfs(int x) {
    D[x] = L[x] = ++ timestamp;
    pre[ii++] = x, instack[x] = 1;
    for(auto i : mp[x]) {
        if(!D[i]) {
            dfs(i);
            L[x] = min(L[x], L[i]);
        }
        else if(instack[i]) {
            L[x] = min(L[x], D[i]);
        }
    }
    if(L[x] == D[x]) {
        sccid ++;
        while(pre[ii] != x) {
            ii --, instack[pre[ii]] = 0;
            id[pre[ii]] = sccid;
        }
    }
    return;
}
int solve() {
    rep(i, 1, n) {
        if(!D[i]) dfs(i);
    }
    rep(i, 1, n) {
        for(auto j : mp[i]) {
            if(id[i] != id[j]) {
                deg[id[j]] ++;
            }
        }
    }
    int ans = 0;
    rep(i, 1, sccid) ans += !deg[i];
    return ans;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        init_();
        rep(i, 1, m) {
            int x, y; cin >> x >> y;
            mp[x].push_back(y);
        }
        cout << solve() << "\n";
    }
    return 0;
}
