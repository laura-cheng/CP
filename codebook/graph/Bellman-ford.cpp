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

