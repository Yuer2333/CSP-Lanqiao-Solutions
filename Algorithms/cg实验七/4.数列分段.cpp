//https://cg.hnu.edu.cn/assignment/programList_ce.jsp?assignID=1596&proNum=4&libCenter=false
//思路：二分答案
//左指针一定为数组中的最大值 右指针为数组的总和
//利用贪心的思想 从第一个元素开始 一旦该段超过限制 将其划为一段
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
typedef long long LL;//一定要注意数据范围
int n,m;
LL a[N];
bool check(LL limit)
{
    int cnt = 1;
    LL sum = 0;
    for(int i = 1;i <= n;++i)
    {
        if(sum +a[i] <= limit)//刚开始错写为<
        {
            sum+=a[i];
        }
        else{
            cnt++;
            sum = a[i];
        }
    }
    return cnt<=m;
}
int main()
{
    cin >> n >> m;
    LL l=0,r=0;
    for(int i = 1;i <= n;++i)
    {
        cin >> a[i];
        l = max(l,a[i]);
        r +=a[i];
    }

    while(l<r)
    {
        LL mid = l +(r-l)/2;
        if(check(mid)) r = mid;
        else l = mid+1;
    }

    cout << l <<'\n';
}