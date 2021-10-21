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
