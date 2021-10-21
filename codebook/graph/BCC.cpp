void dfs(int x, int par) {
    D[x] = L[x] = ++timestamp;
    for(auto i : mp[x]) if(i != par) {
        int to = es[i] ^ x;
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
        else if(D[to] <= D[x]) {
            pre[ii ++] = i;
            L[x] = min(L[x], D[to]);
        }
    }
    return;
}

