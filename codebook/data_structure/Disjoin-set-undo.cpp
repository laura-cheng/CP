struct DSU {
    int n, cnt, op;
    vector<int> par, sz;
    stack<pair<int*, int>> st;
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
        st.push({&par[bb], par[bb]});
        st.push({&sz[aa], sz[aa]});
        par[bb] = aa, sz[aa] += sz[bb];
        return;
    }
    void undo() {
        assert(op);
        rep(i, 0, 1) {
        	pair<int*, int> aa = st.top();
        	st.pop(), *aa.first = aa.second;
        }
        op --, cnt ++;
    }
} dsu;
