#define wiwihorz
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define INF 10000000000000000000
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
struct AC {
	int n, op;
	vector<int> a, b;
	stack<int> st;
	vector<pair<char, int>> ans;
	void init_(int _n) {
		n = _n, op = 0;
		a.assign(n + 1, 0);
		b.assign(n + 1, 0);
		ans.clear();
	}
	void build() { rrep(i, 1, n) st.push(a[i]);}
	void ddo(int L, int R, int l, int r) {
		unordered_map<int, int> cnt;
		vector<int> cur(R - L + 1, 0);
		rep(i, 0, R - L) {
			op ++;
			ans.push_back({'T', 0});
			cnt[st.top()] ++;
			st.pop();
		}
		
		rep(i, l, r) {
			if(cnt.find(b[i]) != cnt.end()) {
				cur[i - l] = b[i];
				cnt[b[i]] --;
				if(cnt[b[i]] == 0) {
					cnt.erase(cnt.find(b[i]));
				}
			}
		}
		rep(i, 0, R - L) {
			if(cur[i] == 0) {
				cur[i] = cnt.begin() -> first;
				
				if(cnt.begin() -> second == 1) {
					cnt.erase(cnt.begin());
				}
				else cnt[cnt.begin() -> first] --;
			}
		}
		rrep(i, 0, R - L) {
			ans.push_back({'P', cur[i]});
			st.push(cur[i]);
		}
		return;
	}
	bool check(int L, int R) {
		unordered_map<int, int> cnt;
		vector<int> temp;
		rep(i, 0, R - L) {
			temp.push_back(st.top());
			st.pop();
			cnt[temp.back()] ++;
		}
		bool yes = 1;
		rep(i, L, R) if(!cnt[b[i]]) yes = 0;
		rep(i, 0, R - L) {
			st.push(temp.back());
			temp.pop_back();
		}
		return yes;
	}
	void solve(int L, int R) {
		if(L == R) {
			op ++;
//			assert(st.top() == b[L]);
			ans.push_back({'T', 0});
			ans.push_back({'U', 0});
			ans.push_back({'P', b[L]});
			return;
		}
		int mid = (L + R) / 2;
		if(!check(L, mid)) ddo(L, R, L, mid);
		solve(L, mid);
		if(!check(mid + 1, R)) ddo(L, R, mid + 1, R);
		solve(mid + 1, R);
		return;
	}
} ac;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int n; cin >> n;
	ac.init_(n);
	rep(i, 1, n) cin >> ac.a[i];
	rep(i, 1, n) cin >> ac.b[i];
	ac.build();
	ac.solve(1, n);
	cout << ac.op << " \n";
	for(auto i : ac.ans) {
		if(i.second == 0) cout << i.first << "\n";
		else cout << i.first << " " << i.second << "\n";
	}
	return 0;
}
