#define wiwihorz
#include <bits/stdc++.h>
#pragma GC optimize("Ofast")
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

signed history(signed);
signed get_experiment_type();
signed get_a();
signed get_b();


struct mat {
	int r, c;
	vector<vector<int>> v;
	mat(int _r, int _c) {
		r = _r, c = _c;
		v.assign(r, vector<int>(c, 0));
	}
	void init_(vector<vector<int>> _v) {
		v = _v;
	}
	void id() {
		v.assign(r, vector<int>(r, 0));
		rep(i, 0, r - 1) v[i][i] = 1;
		return;
	}
	mat operator*(mat b) {
		mat ans = mat(b.r, c);
		rep(i, 0, b.r - 1) rep(j, 0, c - 1) {
			rep(k, 0, b.c - 1) {
				ans.v[i][j] += v[i][k] * b.v[k][j];
			}
			ans.v[i][j] %= MOD;
		} 
		return ans;
	}
	void put() {
		print(r, c);
		rep(i, 0, r - 1) rep(j, 0, c - 1) {
			cerr << v[i][j] << " \n"[j == c - 1];
		}
	}
};
mat mpow(mat a, int times) {
	mat ans = mat(a.r, a.c);
	assert(ans.r == ans.c);
	ans.id();
	for(; times > 0; times >>= 1, a = a * a) {
		if(times & 1) ans = ans * a;
	}
	return ans;
}
int solve1(int t, vector<int> v) {
	mat a = mat(3, 3);
	a.init_({
		{0, 1, 0},
		{1, 1, 1},
		{0, 0, 1}
	});
	a = mpow(a, t);
	int ans = a.v[1][0] * v[1] + a.v[1][1] * v[0] + a.v[1][2];
	ans = (ans % MOD + MOD) % MOD;
	return ans;
}
int solve2(int t, vector<int> v) {
	mat a = mat(6, 6);
	a.init_({
		{2, 1, -3, 0, 1, 4},
		{1, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 1}
	});
	a = mpow(a, t);
	int ans = 0;
	rep(i, 0, 4) ans += a.v[0][i] * v[i];
	ans += a.v[0][5];
	ans = (ans % MOD + MOD) % MOD;
	return ans;
}
int solve3(int t, vector<int> v) {
	mat a = mat(5, 5);
	a.init_({
		{7, -17, 14, 4, -8},
		{1, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0}
	});
	a = mpow(a, t);
	int ans = 0;
	rep(i, 0, 4) ans += a.v[0][i] * v[i];
	ans = (ans % MOD + MOD) % MOD;
	return ans;
}
int solve4(int t, vector<int> v) {
	mat a = mat(4, 4);
	a.init_({
		{6, -3, -4, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0},
		{0, 1, 0, 0}
	});
	int ans = 0;
	if(!(t & 1)) {
		a = mpow(a, t / 2);
		rep(i, 0, 3) ans += a.v[0][i] * v[i];
		ans = (ans % MOD + MOD) % MOD; 
	}
	else {
		a = mpow(a, t / 2 + 1);
		rep(i, 0, 3) ans += a.v[1][i] * v[i];
		ans = (ans % MOD + MOD) % MOD;
	}
	return ans;
}
namespace WA {
	signed predict(int t) {
		vector<int> times(6, 0), v(5, 0), v1(5, 0);
		rep(i, 0, 5) times[i] = history(i);
		rep(i, 0, 4) v[i] = times[i];
		rep(i, 1, 5) v1[i - 1] = times[i];
		int type = 0;
		if(solve1(1, v1) == times[0]) type = 1;
		else if(solve2(1, v1) == times[0]) type = 2;
		else if(solve3(1, v1) == times[0]) type = 3;
		else if(solve4(1, v1) == times[0]) type = 5;
		else type = 4;
		assert(type);
		if(type == 1) return solve1(t, v);
		if(type == 2) return solve2(t, v);
		if(type == 3) return solve3(t, v);
		if(type == 4) return solve4(t, v);
		if(type == 5) return solve4(t + 1, v1);
	}
};

namespace sb2 {
	signed predict(int t) {
		vector<int> times(6, 0), v(5, 0), v1(5, 0);
		rep(i, 0, 5) times[i] = history(i);
		rep(i, 0, 4) v[i] = times[i];
		rep(i, 1, 5) v1[i - 1] = times[i];
		return solve2(t, v);
	}
};
namespace sb3 {
	signed predict(int t) {
		vector<int> times(6, 0), v(5, 0), v1(5, 0);
		rep(i, 0, 5) times[i] = history(i);
		rep(i, 0, 4) v[i] = times[i];
		rep(i, 1, 5) v1[i - 1] = times[i];
		return solve3(t, v);
	}
};
namespace sb4 {
	signed predict(int t) {
		vector<int> times(6, 0), v(5, 0), v1(5, 0);
		rep(i, 0, 5) times[i] = history(i);
		rep(i, 0, 4) v[i] = times[i];
		rep(i, 1, 5) v1[i - 1] = times[i];
		if(solve4(1, v1) == times[0]) {
			return solve4(t + 1, v1);
		}
		else return solve4(t, v);

	}
};
signed predict(int t) {
	return WA::predict(t);
}

