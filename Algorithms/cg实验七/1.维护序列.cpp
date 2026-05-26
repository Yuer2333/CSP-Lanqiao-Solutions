//https://cg.hnu.edu.cn/assignment/programList_ce.jsp?assignID=1596&proNum=1&libCenter=false
//其中包含线段树模板
#include <iostream>
using namespace std;

#define lc p << 1
#define rc p << 1 | 1

typedef long long LL;
const int N = 1e5 + 10;

int n, m;
LL P, a[N];

struct node
{
    int l, r;
    LL sum, mul, add;
} tr[N << 2];

void pushup(int p)
{
    tr[p].sum = (tr[lc].sum + tr[rc].sum) % P;
}

void lazy(int p, LL mul, LL add)
{
    int l = tr[p].l, r = tr[p].r;
    tr[p].sum = (tr[p].sum * mul + (r - l + 1) * add) % P;
    tr[p].mul = tr[p].mul * mul % P;
    tr[p].add = (tr[p].add * mul + add) % P;
}

void pushdown(int p)
{
    if(tr[p].mul != 1 || tr[p].add != 0)
    {
        lazy(lc, tr[p].mul, tr[p].add);
        lazy(rc, tr[p].mul, tr[p].add);
        tr[p].mul = 1;
        tr[p].add = 0;
    }
}

void build(int p, int l, int r)
{
    tr[p] = {l, r, a[l] % P, 1, 0};
    if(l == r) return;

    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}

void modify(int p, int x, int y, LL mul, LL add)
{
    int l = tr[p].l, r = tr[p].r;
    if(x <= l && r <= y)
    {
        lazy(p, mul, add);
        return;
    }

    pushdown(p);

    int mid = (l + r) >> 1;
    if(x <= mid) modify(lc, x, y, mul, add);
    if(y > mid) modify(rc, x, y, mul, add);

    pushup(p);
}

LL query(int p, int x, int y)
{
    int l = tr[p].l, r = tr[p].r;
    if(x <= l && r <= y) return tr[p].sum;

    pushdown(p);

    int mid = (l + r) >> 1;
    LL sum = 0;
    if(x <= mid) sum = (sum + query(lc, x, y)) % P;
    if(y > mid) sum = (sum + query(rc, x, y)) % P;

    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> P;
    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1, 1, n);

    cin >> m;
    while(m--)
    {
        int op, t, g;
        LL c;
        cin >> op >> t >> g;

        if(op == 1)
        {
            cin >> c;
            modify(1, t, g, c % P, 0);
        }
        else if(op == 2)
        {
            cin >> c;
            modify(1, t, g, 1, c % P);
        }
        else
        {
            cout << query(1, t, g) % P << '\n';
        }
    }

    return 0;
}