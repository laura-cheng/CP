void dfs(int x, int par) {
    cnt ++, pre[ii++] = x;
    L[x] = D[x] = ++timestamp;
    for(auto i : mp1[x]) if(i != par) {
        int to = es[i] ^ x;
        if(D[to]) L[x] = min(D[to], L[x]);
        else {
            dfs(to, i);
            L[x] = min(L[x], L[to]);
            if(L[to] >= D[x]) {
                bccid ++;
                mp[n + bccid].push_back(x);
                mp[x].push_back(n + bccid);
                while(pre[ii] != to) {
                    ii --;
                    mp[n + bccid].push_back(to);
                    mp[to].push_back(n + bccid);
                }
            }
        }
    }
    return;
}
