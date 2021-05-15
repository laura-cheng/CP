#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define INF 1e9
#define MAXN 2000

using namespace std;

int n, b[100][MAXN], a[MAXN];
int Secret(int, int);
void build(int d, int L, int R) {
	if(L == R) b[d][L] = a[L];
	else {
		int mid = (L + R) / 2;
		build(d + 1, L, mid);
		build(d + 1, mid + 1, R);
		b[d][mid] = a[mid];
		b[d][mid + 1] = a[mid + 1];
		rrep(i, L, mid - 1) b[d][i] = Secret(a[i], b[d][i + 1]);			
		rep(i, mid + 2, R) b[d][i] = Secret(b[d][i - 1], a[i]);
	}
}
int query(int d, int L, int R, int l, int r) {
	int mid = (L + R) / 2;
	if(l > R || r < L) return INF;
	else if(L == R) return b[d][l];
	else if(l <= mid && r >= mid + 1) 
		return Secret(b[d][l], b[d][r]);
	else {
		int aa = query(d + 1, L, mid, l, r);
		int bb = query(d + 1, mid + 1, R, l, r);
		if(aa > bb) return bb;
		return aa;
	}
}
void Init(int N, int A[]) {
	n = N;
	rep(i, 0, n - 1) a[i] = A[i];
	build(1, 0, n - 1);
	return;
}
int Query(int L, int R) {
	return query(1, 0, n - 1, L, R);
}
