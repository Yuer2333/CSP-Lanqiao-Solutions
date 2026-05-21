#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;
int tree[N][26], p[N], e[N];
int idx = 1; // 根节点是0，新节点从1开始分配

void insert(string &s) {
    int cur = 0;
    p[cur]++;
    for (char ch : s) {
        int path = ch - 'a';
        if (tree[cur][path] == 0) tree[cur][path] = idx++;
        cur = tree[cur][path];
        p[cur]++;
    }
    e[cur]++; // 词频统计：记录以此节点结尾的单词数量
}

struct Node {
    string word;
    int count;
};

vector<Node> ans;

// DFS 遍历字典树，将所有单词及其词频存入 vector
void dfs(int cur, string s) {
    if (e[cur] > 0) {
        ans.push_back({s, e[cur]});
    }
    for (int i = 0; i < 26; i++) {
        if (tree[cur][i] != 0) {
            dfs(tree[cur][i], s + (char)(i + 'a'));
        }
    }
}

// 排序规则：频率由高到低；频率相同时，字典序由小到大
bool cmp(const Node &a, const Node &b) {
    if (a.count != b.count) return a.count > b.count;
    return a.word < b.word;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string temp = "";
    char c;

    // 直接从标准输入读取字符直到结束
    while (cin.get(c)) {
        if (isalpha(c)) {
            temp += (char)tolower(c); // 转小写并拼接到当前单词
        } else {
            if (!temp.empty()) {
                insert(temp); // 遇到非字母，且 temp 不为空，说明一个单词结束
                temp = "";
            }
        }
    }
    // 处理文本末尾可能剩下的单词
    if (!temp.empty()) insert(temp);

    // 1. 提取单词
    dfs(0, "");

    // 2. 排序
    sort(ans.begin(), ans.end(), cmp);

    // 3. 按要求输出前100个
    int limit = min((int)ans.size(), 100);
    for (int i = 0; i < limit; i++) {
    	if(i!=limit-1) cout << ans[i].word << " " << ans[i].count << endl;
    	else cout << ans[i].word << " " << ans[i].count;
        
    }

    return 0;
}
