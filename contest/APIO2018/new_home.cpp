    #define wiwihorz
    #include <bits/stdc++.h>
    #pragma GCC optimize("Ofast")
    #pragma loop-opt(on)
     
    #define rep(i, a, b) for(int i = a; i <= b; i++)
    #define rrep(i ,a, b) for(int i = b; i >= a; i--)
    #define all(x) x.begin(), x.end()
    #define ceil(a, b) ((a + b - 1) / (b))
     
    #define INF 1e9
    #define MOD 1000000007
    #define eps (1e-9)
     
    using namespace std;
    #define lld long double
    #define pii pair<int, int>
    #define random mt19937 rnd(chrono::steady_clock::now().times_since_epoch().count())
     
    #ifdef wiwihorz
    #define print(a...) kout("[" + string(#a) + "] = ", a)
    void vprint(auto L, auto R) { while(L < R) cerr << *L << " \n"[next(L) == R], ++L;}
    void kout() { cerr << endl; }
    template<class T1, class ... T2> void kout(T1 a, T2 ... e) { cerr << a << " ", kout(e...);}
    #else
    #define print(...) 0
    #define vprint(...) 0
    #endif
    namespace solver {
    	int n, k;
    	vector<int> x, t, a, b, mn;
    	void init_(int _n, int _k) {
    		n = _n, k = _k;
    		x.assign(n + 1, 0);
    		t.assign(n + 1, 0);
    		a.assign(n + 1, 0);
    		b.assign(n + 1, 0);
    		mn.assign(k + 1, 0);
    	}
    	int query(int l, int y) {
    		mn.assign(k + 1, INF);
    		rep(i, 1, n) if(a[i] <= y && b[i] >= y) {
    			mn[t[i]] = min(mn[t[i]], abs(l - x[i]));
    		}
    		int ans = 0;
    		rep(i, 1, k) ans = max(ans, mn[i]);
    		if(ans == INF) return -1;
    		return ans;
    	}
    };
    using namespace solver;
    signed main() {
    	ios::sync_with_stdio(false), cin.tie(0);
    	int n, k, q; cin >> n >> k >> q;
    	init_(n, k);
    	rep(i, 1, n) {
    		cin >> x[i] >> t[i];
    		cin >> a[i] >> b[i];
    	}
    	rep(i, 1, q) {
    		int l, y; cin >> l >> y;
    		cout << query(l, y) << "\n";
    	}	
    	return 0;
    }
