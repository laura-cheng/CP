#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> pii;
//(value, cnt)

const int N = 2000006;
const LL INF = (1LL<<50);

int d[N];

pii cal(int n,int mid)
{
    pii mx = {0,0},buy_mx = {-INF,-1};
    for (int i=1;n>=i;i++)
    {
        pii tmp = { mx.first - d[i] - mid,mx.second-1 };
        mx = max(mx,{buy_mx.first + d[i] , buy_mx.second});
        buy_mx = max( buy_mx,tmp );
    }
    return mx;
}

int main ()
{
    int n,k;
    scanf("%d %d",&n,&k);
    for (int i=1;n>=i;i++)
    {
        scanf("%d",&d[i]);
    }
    int L=-1,R = 10000005;
    while (R-L != 1)
    {
        int mid=(L+R)>>1; //cost
        pii tmp = cal(n,mid);
        if (-tmp.second <= k) R=mid;
        else L=mid;
    }
    if (R==0)
    {
        pii tmp = cal(n,R);
        printf("%lld\n",tmp.first);
    }
    else
    {
        LL smaller = R;
        LL bigger = R-1;
        pii tmp_small = cal(n,smaller);
        pii tmp_big = cal(n,bigger);
        LL small_cnt = -tmp_small.second;
        LL big_cnt = -tmp_big.second;
        LL p_small = tmp_small.first + small_cnt * smaller;
        LL p_big = tmp_big.first + big_cnt * bigger;
        printf("%lld\n",p_small + (p_big - p_small) * (k - small_cnt) / (big_cnt - small_cnt));
    }
}

