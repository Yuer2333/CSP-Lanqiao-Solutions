//https://cg.hnu.edu.cn/assignment/programList_ce.jsp?assignID=1596&proNum=3&libCenter=false
//某一区间的值同时升高 可运用差分算法
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
typedef long long LL;

LL diff[N];
int n, q;
LL s, t;

LL calc(LL d)
{
    if (d > 0) return -d * s;
    return -d * t;//d < 0 升高t度
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> s >> t;

    LL last = 0;
    LL tmp = 0;

    for (int i = 0; i <= n; ++i)
    {
        LL x;
        cin >> x;

        if (i >= 1)
        {
            diff[i] = x - last;
            tmp += calc(diff[i]);
        }

        last = x;//省空间，无需再建数组
    }

    while (q--)
    {
        int l, r;
        LL x;
        cin >> l >> r >> x;

        tmp -= calc(diff[l]);
        diff[l] += x;
        tmp += calc(diff[l]);

        if (r + 1 <= n)
        {
            tmp -= calc(diff[r + 1]);
            diff[r + 1] -= x;
            tmp += calc(diff[r + 1]);
        }

        cout << tmp << '\n';
    }

    return 0;
}