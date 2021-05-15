#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i ++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a ,b) ((a + b - 1) / (b))

#define INF 1000000000000000000
#define MOD 1000000007
#define MAXN 1000005
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
}
void kout() { cerr << endl; }
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif

signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int t; cin >> t;
	while(t --) {
		int n; cin >> n;
		vector<int> a(n, 0);
		rep(i, 0, n - 1) cin >> a[i];
		sort(all(a));
		pii cur = {0, a[0]};
		priority_queue<pii> pq;
		rep(i, 0, n - 1) {
			if(a[i] == cur.second) cur.first ++;
			else {
				pq.push(cur);
				cur = {1, a[i]};
			}
		}
		pq.push(cur);
		while(pq.size() > 1) {
			pii aa = pq.top(); pq.pop();
			pii bb = pq.top(); pq.pop();
			aa.first --, bb.first --;
			if(aa.first) pq.push(aa);
			if(bb.first) pq.push(bb);
 		}
 		if(pq.size()) cout << pq.top().first << "\n";
		else cout << "0\n";
	}	
	return 0;
}

