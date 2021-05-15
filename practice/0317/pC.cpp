#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define ceil(a, b) ((a + b - 1) / (b))
#define all(x) x.begin(), x.end()

#define INF 1000000000000000000
#define MOD 1000000007
#define eps (1e-9)
#define MAXN 1000005

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++ L;
}
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
struct AC {
	int n, k;
	vector<int> a;
	vector<vector<int>> ans;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, 0);
	}
	void solve() {
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		rep(i, 1, n) {
			pq.push({a[i], i});
		}
		while(pq.size()) {
			if(pq.size() < k) {
				cout << "-1\n";
				return;
			}
			int x = pq.top().first;
			vector<pii> temp;
			ans.push_back(vector<int>(k + 1, 0));
			ans[ans.size() - 1][0] = x;
			rep(i, 1, k) {
				pii cur = pq.top(); pq.pop();
				ans[ans.size() - 1][i] = cur.second;
				cur.first -= x;
				temp.push_back(cur);
			}
			for(auto i : temp) {
				if(i.first) pq.push(i);
			}
		}
		cout << ans.size() << "\n";
		for(auto i : ans) {
			rep(j, 0, k) {
				cout << i[j] << " \n"[j == k];
			}
		}
	}

};
struct sb4 {
	int n, k;
	vector<int> a;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, 0);
		return;
	}
	void solve() {	
		if(n % k != 0) {
			assert(0);
			cout << "-1\n";
			return;
		}
		cout << n / k << "\n";
		rep(i, 1, n / k) {
			cout << a[1];
			rep(j, (i - 1) * k + 1, i * k) {
				cout << " " << j;
			}
			cout << "\n";
		}
		return;
	}

};
struct sb3 {
	int n, k;
	vector<int> a;
	vector<vector<int>> ans;
	void init_(int _n, int _k) {
		n = _n, k = _k;
		a.assign(n + 1, 0);
		return;
	}
	void fail() {
		cout << "-1\n";
	}
	void solve() {	
		int sum = 0;
		rep(i, 1, n) sum += a[i];
		if(sum % k) {
			fail();
			return;
		}
		set<pii> s;
		rep(i, 1, n) {
			s.insert({a[i], -i});
		}
		rep(i, 1, n) {
			if(!a[i]) continue;
			if(i != n && a[i] && a[i + 1] == 0) {
				fail(); return;
			}
			auto it = s.lower_bound({a[i], -i});
			pii cur = *it; s.erase(it);
			ans.push_back(vector<int>(k + 1, 0));
			ans[ans.size() - 1][0] = cur.first;
			ans[ans.size() - 1][1] = i;
			a[i] = 0;
			rep(j, 2, k) {
				if(!s.size() || s.rbegin() -> first < cur.first) {
					fail();
					return;
				}
				auto it1 = prev(s.end()); 
				pii now = *it1;
				s.erase(it1);
				ans[ans.size() - 1][j] = -now.second;
				now.first -= cur.first;
				a[-now.second] -= cur.first;
				if(now.first) s.insert(now);
			}
		}
		cout << ans.size() << "\n";
		for(auto i : ans) {
			rep(j, 0, k) {
				cout << i[j] << " \n"[j == k];
			}
		}
	}

} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n, k; cin >> n >> k;
	ac.init_(n, k);
	rep(i, 1, n) cin >> ac.a[i];
	ac.solve();
	
	return 0;
}


