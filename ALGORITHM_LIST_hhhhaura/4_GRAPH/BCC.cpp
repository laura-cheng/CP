#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i ,a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define MAXN 1000005
#define INF 1000000000000000000
#define eps (1e-9)
#define MOD 1000000007

//#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a )
void vprint(auto L, auto R) {
    while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
    cerr << a << " ", kout(e...);
}
#else
#define print(...) 0
#define vprint(..) 0
#endif // wiwihorz
struct DSU {
    int n, op;
    vector<int> par, sz;
    stack<pair<int*, int>> sz_stack, par_stack;
    void init_(int _n) {
        n = _n, op = 0;
        sz.assign(n + 1, 0);
        par.assign(n + 1, 0);
        rep(i, 1, n) par[i] = i;
    }
    int find_par(int a) {
        while(par[a] != a) a = par[a];
        return par[a];
    }
    void unite(int a, int b) {
        int aa = find_par(a);
        int bb = find_par(b);
        if(aa == bb) return;
        op ++;
        if(sz[aa] < sz[bb] ) swap(aa, bb);
        sz_stack.push({&sz[aa], sz[aa]});
        par_stack.push({&par[bb], par[bb]});
        par[bb] = aa, sz[aa] += sz[bb];
        return;
    }
    void undo() {
        if(!op) return;
        pair<int*, int> aa, bb;
        aa = sz_stack.top(), sz_stack.pop();
        bb = par_stack.top(), par_stack.pop();
        *aa.first = aa.second;
        *bb.first = bb.second;
        op --;
        return;
    }
    bool same(int a, int b) {
        return find_par(a) == find_par(b);
    }
} dsu;
vector<int> x, y, es, L, D, pre;
vector<vector<int>> mp, bcc;
int ii, bccid, timestamp, n, m, temp[1500][1500];
void init_() {
    x.clear(), y.clear();
    es.clear(), bcc.clear();
    L.assign(n + 1, 0);
    D.assign(n + 1, 0);
    mp.assign(n + 1, vector<int>());
    rep(i, 0, n * n) pre[i] = -1;
    rep(i, 0, n + 1) rep(j, 0, n + 1) temp[i][j] = 0;
    ii = timestamp = 0;
    bccid = -1;
    return;
}
void add_edge(int a, int b) {
//    print(a, b);
    x.push_back(a);
    y.push_back(b);
    es.push_back(a ^ b);
    mp[a].push_back(x.size() - 1);
    mp[b].push_back(x.size() - 1);
    return;
}
void dfs(int x, int par) {
    D[x] = L[x] = ++timestamp;
//    print(x);
    for(auto i : mp[x]) {
        int to = es[i] ^ x;
        if(par == i) continue;

        if(!D[to]) {
            pre[ii ++] = i;
            dfs(to, i);
            L[x] = min(L[x], L[to]);
            if(D[x] <= L[to]) {
                bccid ++;
                bcc.push_back(vector<int>());
                while(pre[ii] != i) {
                    ii --, bcc[bccid].push_back(pre[ii]);
                }
            }
        }
        else if(D[to] < D[x]) {
            pre[ii ++] = i;
            L[x] = min(L[x], D[to]);
        }
    }
    return;
}
int solve() {
    rep(i, 1, n) if(!D[i]) {
        dfs(i, -1);
        assert(ii == 0);

    }
    dsu.init_(2 * n);
    vector<bool> yes(n + 1, 0);
    rep(i, 0, bccid) {
        int cur = dsu.op, good = 0;
        for(auto j : bcc[i]) {
            dsu.unite(x[j], y[j] + n);
            dsu.unite(x[j] + n, y[j]);
            if(dsu.same(x[j], y[j])) good = 1;
        }
        if(good) for(auto j : bcc[i]) {
            yes[x[j]] = 1;
            yes[y[j]] = 1;
        }
        while(dsu.op!=cur) dsu.undo();
    }
    int ans = 0;
    rep(i, 1, n) ans += yes[i];
    return n - ans;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    pre.assign(MAXN, 0);
    while(cin >> n >> m && (n || m)) {
        init_();
        rep(i, 1, m) {
            int a, b; cin >> a >> b;
            temp[a][b] = temp[b][a] = 1;
        }
        rep(i, 1, n) rep(j, i + 1, n) {
            if(!temp[i][j]) add_edge(i, j);
        }
        cout << solve() << "\n";
    }
    return 0;
}
