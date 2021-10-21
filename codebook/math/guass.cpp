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
