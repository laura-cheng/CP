void dfs(int x) {
    D[x] = L[x] = ++ timestamp;
    pre[ii++] = x, instack[x] = 1;
    for(auto i : mp[x]) {
        if(!D[i]) dfs(i), L[x] = min(L[x], L[i]);
        else if(instack[i]) L[x] = min(L[x], D[i]);
    }
    if(L[x] == D[x]) {
        sccid ++;
        while(pre[ii] != x) {
            ii --, instack[pre[ii]] = 0;
            id[pre[ii]] = sccid;
        }
    }
    return;
}
