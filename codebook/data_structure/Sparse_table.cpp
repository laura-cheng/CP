int n, lg;
vector<int> a;
vector<vector<int>> st;
void build() {
    lg = 32 - __builtin_clz(n);
    st.assign(lg + 1, vector<int>(n + 1, -INF));
    rep(i, 1, n) st[0][i] = a[i];
    rep(i, 1, lg) rep(j, 1, n) {
        st[i][j] =
        max(
            st[i - 1][j],
            st[i - 1][j + (1 << (i - 1))]
        );
    }
    return;
}
int query(int L, int R) {
    int x = 31 - __builtin_clz(R - L + 1);
    return max(st[x][L], st[x][R - (1 << x) + 1]);
}
