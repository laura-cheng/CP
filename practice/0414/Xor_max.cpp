#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define rrep(i, a, b) for(int i = b; i >= a; --i)
#define all(x) x.begin(), x.end()

using namespace std;
#define MAXP 40000000
int p = 0, sz[MAXP], ch[MAXP][2];
int get_new() {
    ++p, sz[p] = 0;
    ch[p][0] = ch[p][1] = 0;
    return p;
}
struct trie {
	static const int H= 31;
	int size, root, best_ans;
	vector<int> nums;
	void init_() {
		size = 0, root = get_new();
		best_ans = 0;
		nums.clear();
	}
	void pull(int nd) {sz[nd] = sz[ch[nd][0]] + sz[ch[nd][1]];}
	void merge(trie &b) {
		best_ans = max(best_ans, b.best_ans);
		for(auto i : b.nums) add(i);
	}
	int query(int nd, int h, bitset<H> a) {
		if(h == 0 || !nd) return 0;
		else {
		  bool flag = a[h - 1];
		  if(sz[ch[nd][!flag]]) return ((!flag) << (h - 1)) | query(ch[nd][!flag], h - 1, a);
		  else return ((flag) << (h - 1)) | query(ch[nd][flag], h - 1, a);
		}
	}
	void insert(int nd, int h, bitset<H> a) {
		if(h == 0) {
		    sz[nd] ++;
		    return;
		}
		if(!ch[nd][a[h - 1]]) ch[nd][a[h - 1]] = get_new();
		insert(ch[nd][a[h - 1]], h - 1, a);
		pull(nd);
	}
	int ask(int x) {return x ^ query(root, H, bitset<H>(x));}
	void add(int x) {
		size ++, nums.push_back(x);
		if(size >= 2) best_ans = max(best_ans, ask(x));
		insert(root, H, bitset<H>(x));
	}
};
namespace dsu {
	int n;
	vector<int> sz, par;
	vector<trie> T;
	void init_(int _n) {
		n = _n;
		sz.assign(n + 1, 1);
		par.assign(n + 1, 0);
		T.assign(n + 1, trie());
		rep(i, 1, n) {par[i] = i;}
	}
	int find_par(int x) {
		while(x != par[x]) x = par[x];
		return x;
	}
	int best(int a) {
		int aa = find_par(a);
		return T[aa].best_ans;
	}
	void unite(int a, int b) {
		int aa = find_par(a);
		int bb = find_par(b);
		if(aa == bb) return;
		if(sz[aa] < sz[bb]) swap(aa, bb);
		T[aa].merge(T[bb]);
		sz[aa] += sz[bb];
		par[bb] = aa;
	} 
	
};
namespace solver {
	int n, best;
	vector<int> a, b, ans;
	vector<bool> vis;
	void init_(int _n) {
		n = _n, best = 0;
		dsu::init_(n);
		a.assign(n + 1, 0);
		vis.assign(n + 2, 0);
		b.clear();
		ans.clear();
	}	
	void solve() {
	    rep(i, 0, n) dsu::T[i].init_();
	    dsu::T[0].add(0);
		rep(i, 1, n) {
		    a[i] ^= a[i - 1];
		    dsu::T[i].add(a[i]);
		}
		reverse(all(b));
		for(auto i : b) {
			vis[i] = 1;
			dsu::unite(i - 1, i);
			best = max(best, dsu::best(i));
			ans.push_back(*s.rbegin());
		}
		reverse(all(ans));
		return;
	} 
};
using namespace solver;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	init_(n);
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) {
		int x; cin >> x;
		b.push_back(x);
	}
	solve();
	rep(i, 0, n - 1) cout << ans[i] << " \n"[i + 1 == n];
	return 0;
}
