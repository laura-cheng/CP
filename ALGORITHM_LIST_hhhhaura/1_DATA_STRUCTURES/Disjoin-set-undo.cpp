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
struct DSU {
    int n, cnt, op;
    vector<int> par, sz;
    stack<pair<int*, int>> par_stack, sz_stack;
    void init_(int _n) {
        n = _n, cnt = n, op = 0;
        par.assign(n + 1, 0);
        sz.assign(n + 1, 1);
        rep(i, 1, n) par[i] = i;
        return;
    }
    int find_par(int a) {
        while(par[a] != a) a = par[a];
        return par[a];
    }
    bool same(int a, int b) {
        return find_par(a) == find_par(b);
    }
    void unite(int a, int b) {
        int aa = find_par(a);
        int bb = find_par(b);
        if(aa == bb) return;
        cnt --, op ++;
        if(sz[aa] < sz[bb]) swap(aa, bb);
        par_stack.push({&par[bb], par[bb]});
        sz_stack.push({&sz[aa], sz[aa]});
        par[bb] = aa, sz[aa] += sz[bb];
        return;
    }
    void undo() {
        assert(op);
        pair<int*, int> aa, bb;
        aa = par_stack.top(), par_stack.pop();
        bb = sz_stack.top(), sz_stack.pop();
        *aa.first = aa.second;
        *bb.first = bb.second;
        op --, cnt ++;
    }
} dsu;
int n, m, k;
vector<pii> es;
vector<int> c, yes;
bool cmp(pii a, pii b) {
    if(c[a.first] != c[b.first]) {
        return c[a.first] < c[b.first];
    }
    else return c[a.second] < c[b.second];
}
bool same(pii a, pii b) {
    return c[a.first] == c[b.first] &&
        c[a.second] == c[b.second];
}
int solve(){
    int bad = 0, ans = k * (k - 1);
    int cur = dsu.op, good = 1;
    pii pre = {0, 0};
    rep(i, 1, k) bad += !yes[i];
    sort(all(es), cmp);
    for(auto i : es) {
        if(!same(i, pre)) {
            while(dsu.op != cur) dsu.undo();
            good = 1, cur = dsu.op;
            pre = i;
        }
        if(!yes[c[i.first]] || !yes[c[i.second]] || !good) continue;
        dsu.unite(i.first, i.second + n);
        dsu.unite(i.first + n, i.second);
        if(dsu.same(i.first, i.second)) ans -=2, good = 0;
    }

    ans -= 2 * bad * (k - bad) + bad * (bad - 1);
    return ans / 2;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> m >> k;
    c.assign(n + 1, 0);
    yes.assign(k + 1, 1);
    dsu.init_(2 * n);
    rep(i, 1, n) cin >> c[i];
    rep(i, 1, m) {
        int x, y; cin >> x >> y;
        if(c[x] > c[y]) swap(x, y);
        es.push_back({x, y});
        if(c[x] == c[y]) {
            dsu.unite(x, y + n) ;
            dsu.unite(x + n, y);
            if(dsu.same(x, y)) yes[c[x]] = 0;
        }
    }
    cout << solve() << "\n";
    return 0;
}


