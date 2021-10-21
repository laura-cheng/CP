void dfs(int x, int par) {
	D[x] = L[x] = ++timestamp;
	int ch = 0, isap = 0;
	for(auto i : mp[x]) if(i != par) {
		if(!D[i]) {
			dfs(i, x), ch ++;
			L[x] = min(L[x], L[i]);
		}
		else L[x] = min(L[x], D[i]);
		if(L[i] >= D[x]) isap = 1;
	}
	if(x == par && ch < 2) isap = 0;
	if(isap) ap.push_back(x);
}

