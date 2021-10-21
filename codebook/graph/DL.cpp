void dfs(int x, int par) {
	L[x] = D[x] = ++timestamp;
	for(auto i : mp[x]) if(i != par) {
		int to = es[i] ^ x;
		if(!D[to]) { // 樹邊
			dfs(to, i);
			L[x] = min(L[x], L[to]);
		} 
		else L[x] = min(L[x], D[to]); 
	} 
	return;
}
