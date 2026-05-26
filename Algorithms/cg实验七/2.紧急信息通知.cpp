//https://cg.hnu.edu.cn/assignment/programList.jsp?proNum=2&courseID=110&assignID=1596&libCenter=false
//思路：构建图结构，直接bfs广度优先搜索，判断是否能够遍历完所有顶点
#include <bits/stdc++.h>
using namespace std;
int n,m;//n个人 m个边
vector<vector<int>> edges;
vector<bool> vis;
const int N = 1e3+5;
bool bfs()
{
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while(!q.empty())
    {
        auto u = q.front();q.pop();
        for(auto v:edges[u])
        {
            if(vis[v]) continue;
            vis[v] = true;
            q.push(v);
        }
    }
    for(int i = 1;i <= n;++i)
    {
        if(vis[i]==false) return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
while (cin >> n >> m) {
    if (n == 0 && m == 0) break;

    edges.assign(N, vector<int>());
    vis.assign(N, false);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    cout << (bfs() ? "Yes" : "No") << '\n';
}
    return 0;
}