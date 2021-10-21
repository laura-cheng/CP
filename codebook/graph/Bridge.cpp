void dfs(int x, int par) {
	L[x] = D[x] = ++timestamp;
	for(auto i : mp[x]) if(i != par) {
		int to = es[i] ^ x;
		if(!D[to]) {
			dfs(to, i);
			L[x] = min(L[x], L[to]);
		} 
		else L[x] = min(L[x], D[to]);
		if(L[to] > D[x]) bridge.push_back(i);
	} 
	return;
}
