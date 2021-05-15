#include <iostream>

#define MAX_N                  1000
#define MAX_Q                 10000
#define MAX_VALUE        1000000000

#define rrep(i, a, b) for(int i = b; i >= a; i--)
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))
#define INF 1e9
#define MAXN 2000

static int N;
static int A[MAX_N];
static int Q;
static int L[MAX_Q];
static int R[MAX_Q];

static int secret_count;

int n, b[100][MAXN], a[MAXN];

int Secret(int X, int Y) {
  ++secret_count;
  if (!(0 <= X && X <= MAX_VALUE)) {
    fprintf(stderr, "Wrong Answer [1]\n");
    exit(0);
  }
  if (!(0 <= Y && Y <= MAX_VALUE)) {
    fprintf(stderr, "Wrong Answer [1]\n");
    exit(0);
  }
  return (X + 2 * (Y / 2) < MAX_VALUE) ? (X + 2 * (Y / 2)) : MAX_VALUE;
}
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


int main() {
  int i, j;
  int secret_count_by_init;
  int max_secret_count_by_query = 0;

  if (1 != scanf("%d", &N)) {
    fprintf(stderr, "error: cannot read N.\n");
    exit(1);
  }
  if (!(1 <= N && N <= MAX_N)) {
    fprintf(stderr, "error: N is out of bounds.\n");
    exit(1);
  }
  for (i = 0; i < N; ++i) {
    if (1 != scanf("%d", &A[i])) {
      fprintf(stderr, "error: cannot read A[%d].\n", i);
      exit(1);
    }
    if (!(0 <= A[i] && A[i] <= MAX_VALUE)) {
      fprintf(stderr, "error: A[%d] is out of bounds.\n", i);
      exit(1);
    }
  }
  if (1 != scanf("%d", &Q)) {
    fprintf(stderr, "error: cannot read Q.\n");
    exit(1);
  }
  if (!(0 <= Q && Q <= MAX_Q)) {
    fprintf(stderr, "error: Q is out of bounds.\n");
    exit(1);
  }
  for (j = 0; j < Q; ++j) {
    if (2 != scanf("%d%d", &L[j], &R[j])) {
      fprintf(stderr, "error: cannot read L[%d] and R[%d].\n", j, j);
      exit(1);
    }
    if (!(0 <= L[j] && L[j] <= R[j] && R[j] <= N - 1)) {
      fprintf(stderr,
              "error: L[%d] and R[%d] do not satisfy the constraints.\n",
              j, j);
      exit(1);
    }
  }

  secret_count = 0;
  Init(N, A);
  secret_count_by_init = secret_count;

  for (j = 0; j < Q; ++j) {
    secret_count = 0;
    printf("%d\n", Query(L[j], R[j]));
    if (max_secret_count_by_query < secret_count) {
      max_secret_count_by_query = secret_count;
    }
  }

  fprintf(stderr, "number of calls to Secret by Init : %d\n",
          secret_count_by_init);
  fprintf(stderr, "maximum number of calls to Secret by Query : %d\n",
          max_secret_count_by_query);

  return 0;
}
