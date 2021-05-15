
#include <bits/stdc++.h>
#include <bits/extc++.h>

#define StarBurstStream ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define iter(a) a.begin(), a.end()
#define riter(a) a.rbegin(), a.rend()
#define lsort(a) sort(iter(a))
#define gsort(a) sort(riter(a))
#define pb(a) push_back(a)
#define eb(a) emplace_back(a)
#define pf(a) push_front(a)
#define ef(a) emplace_front(a)
#define pob pop_back()
#define pof pop_front()
#define mp(a, b) make_pair(a, b)
#define F first
#define S second
#define mt make_tuple
#define gt(t, i) get<i>(t)
#define iceil(a, b) (((a) + (b) - 1) / (b))
#define tomax(a, b) ((a) = max((a), (b)))
#define tomin(a, b) ((a) = min((a), (b)))
#define topos(a) ((a) = (((a) % MOD + MOD) % MOD))
#define uni(a) a.resize(unique(iter(a)) - a.begin())
#define printv(a, b) {bool pvaspace=false; \
for(auto pva : a){ \
    if(pvaspace) b << " "; pvaspace=true;\
    b << pva;\
}\
b << "\n";}

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;
using tiii = tuple<int, int, int>;

const ll MOD = 1000000007;
const ll MAX = 2147483647;

template<typename A, typename B>
ostream& operator<<(ostream& o, pair<A, B> p){
    return o << '(' << p.F << ',' << p.S << ')';
}

int n, k;

vector<vector<vector<int>>> dp;
vector<int> sz;
vector<vector<int>> g;
vector<int> v;

void dfs(int now, int p){
    sz[now] = 1;

    int mx = -1;
    for(int i : g[now]){
        if(i == p) continue;
        dfs(i, now);
        if(mx == -1 || sz[i] > sz[mx]) mx = i;
        sz[now] += sz[i];
    }

    dp[now].resize(2 * n + 1, vector<int>(2));
    dp[now][0][0] = dp[now][0][1] = v[now];
    if(mx == -1){
        return;
    }

    for(int i = 0; i <= 2 * (sz[mx] - 1); i++){
        dp[now][i + 2][0] = v[now] + dp[mx][i][0];
        dp[now][i + 1][1] = v[now] + dp[mx][i][1];
    }
    vector<vector<int>>().swap(dp[mx]);

    for(int i : g[now]){
        if(i == p || i == mx) continue;
        vector<vector<int>> tdp = dp[now];
        for(int j = 0; j <= 2 * (sz[i] - 1); j++){
            for(int l = 0; l <= 2 * n; l++){
                if(j + 2 + l <= 2 * n) tdp[j + 2 + l][0] = max(tdp[j + 2 + l][0], dp[now][l][0] + dp[i][j][0]);
                if(j + 1 + l <= 2 * n) tdp[j + 1 + l][1] = max(tdp[j + 1 + l][1], dp[now][l][0] + dp[i][j][1]);
                if(j + 2 + l <= 2 * n) tdp[j + 2 + l][1] = max(tdp[j + 2 + l][1], dp[now][l][1] + dp[i][j][0]);
            }
        }
        dp[now] = tdp;
        vector<vector<int>>().swap(dp[i]);
    }
}

int main(){
    StarBurstStream

    cin >> n >> k;

    k = min(k, 2 * n);

    dp.resize(n + 1);
    sz.resize(n + 1);
    g.resize(n + 1);
    v.resize(n + 1);

    for(int i = 1; i <= n; i++) cin >> v[i];

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }

    dfs(1, 1);

    int ans = 0;
    for(int i = 0; i <= k; i++){
        ans = max({ans, dp[1][i][0], dp[1][i][1]});
    }
    cout << ans << "\n";

    return 0;
}



