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
vector<int> p, fac;
void build() {
    fac.assign(MAXN, 1);
    rep(i, 2, MAXN - 1) {
        if(fac[i] == 1) p.push_back(i);
        for(auto j : p) {
            if(i * j >= MAXN) break;
            fac[i * j] = j;
            if(i % j == 0) break;
        }
    }
    return;
}
vector<pii> deco(int x) {
    vector<pii> ans;
    while(fac[x] != 1) {
        if(ans.size() && fac[x] ==
           ans[ans.size() - 1].first) {
           ans[ans.size() - 1].second ++;
        }
        else ans.push_back({fac[x], 1});
        x /= fac[x];
    }
    if(ans.size() && x == ans[ans.size() - 1].first)
        ans[ans.size() - 1].second ++;
    else ans.push_back({x, 1});
    return ans;
}
signed main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n; cin >> n;
    build();
    vector<pii> ans = deco(n);
    rep(i, 0, ans.size() - 1) {
        //2^2 * 5
        if(ans[i].second == 1) cout << ans[i].first;
        else cout << ans[i].first << "^" << ans[i].second;
        if(i + 1 == ans.size()) cout << "\n";
        else cout << " * ";
    }
    return 0;
}
