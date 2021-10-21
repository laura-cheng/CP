#define MAXP 1000005
int n, m, p, root, a, b, c, d, e;
struct node {
	int lch, rch, pri, sz;
	int mn, val, tag, rev;
	node() {
		lch = rch = 0, sz = 1;
		pri = rand(), mn = INF;
		val = tag = rev = 0;
	}
}trp[MAXP];
int get_new() {
	++p, trp[p].pri = rand();
	return p;
}
void pull(int nd) {
	int lch = trp[nd].lch, rch = trp[nd].rch;
	trp[nd].sz = 1 + trp[lch].sz + trp[rch].sz;
	trp[nd].mn = min(
		min(trp[nd].val, trp[lch].mn + trp[lch].tag),
		trp[rch].mn + trp[rch].tag
	);
}
void push(int nd) {
	int lch = trp[nd].lch, rch = trp[nd].rch;
	if(trp[nd].tag) {
		trp[nd].val += trp[nd].tag;
		trp[nd].mn += trp[nd].tag;
		trp[lch].tag += trp[nd].tag;
		trp[rch].tag += trp[nd].tag;
		trp[nd].tag = 0;
	}
	if(trp[nd].rev) {
		trp[lch].rev ^= 1;
		trp[rch].rev ^= 1;
		swap(trp[nd].lch, trp[nd].rch);
		trp[nd].rev = 0;
	}
	return;
}
int merge(int pre, int suf) {
	if(pre == 0) return suf;
	if(suf == 0) return pre;
	push(pre), push(suf);
	if(trp[pre].pri > trp[suf].pri) {
		trp[pre].rch = merge(trp[pre].rch, suf);
		pull(pre);
		return pre;
	}
	else {
		trp[suf].lch = merge(pre, trp[suf].lch);
		pull(suf);
		return suf;
	}
}
pii split(int nd, int k) {
	if(nd == 0) return pii(0, 0);
	push(nd);
	int lch = trp[nd].lch, rch = trp[nd].rch;
	if(trp[lch].sz >= k) {
		pii p = split(lch, k);
		trp[nd].lch = p.second;
		pull(nd);
		return pii(p.first, nd);
	}
	else {
		pii p = split(rch, k - trp[lch].sz - 1);
		trp[nd].rch = p.first;
		pull(nd);
		return pii(nd, p.second);	
	}
}
void insert(int id, int val) {
	pii p = split(root, id );
	int nd = get_new();
	trp[nd].val = trp[nd].mn = val;
	root = merge(merge(p.first, nd), p.second);
	return;
}
void reve(int l, int r) {
	pii p = split(root, l - 1);
	a = p.first, p = split(p.second, r - l + 1);
	b = p.first, c = p.second;
	trp[b].rev ^= 1;
	root = merge(merge(a, b), c);
	return;
}
void revo(int l, int r, int t) {
	pii p = split(root, l - 1);
	a = p.first, p = split(p.second, r - l + 1);
	b = p.first, c = p.second;
	int k = (t % (r - l + 1) + (r - l + 1)) % (r - l + 1);
	p = split(b, r - k - l + 1);
	root = merge(merge(a, p.second), merge(p.first, c));
	return;
}
void add(int l, int r, int val) {
	pii p = split(root, l - 1);
	a = p.first, p = split(p.second, r - l + 1);
	b = p.first, c = p.second;
	trp[b].tag += val;
	root = merge(merge(a, b), c);
	return;
}
void erase(int id) {
	pii p = split(root, id);
	c = p.second;
	p = split(p.first, id - 1);
	root = merge(p.first, c);
	return;
}
int query(int l, int r) {
	pii p = split(root, l - 1);
	a = p.first, p = split(p.second, r - l + 1);
	b = p.first, c = p.second;
	int ans = trp[b].mn + trp[b].tag;
	root = merge(merge(a, b), c);
	return ans; 
}
void trav(int nd) {
	if(!nd) return;
	push(nd);
	trav(trp[nd].lch);
	cerr << trp[nd].val << " ";
	trav(trp[nd].rch);
	return;
}
