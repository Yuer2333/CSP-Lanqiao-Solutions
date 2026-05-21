#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

const int N = 1e6 + 10;
int tree[N][26], p[N], e[N];
int idx = 1; // 根节点是0，新分配的节点从1开始，确保tree[cur][path]==0逻辑正确

void insert(string &s) {
    int cur = 0;
    p[cur]++;
    for (auto ch : s) {
        int path = ch - 'a';
        if (tree[cur][path] == 0) tree[cur][path] = idx++;
        cur = tree[cur][path];
        p[cur]++;
    }
    e[cur]++; // 记录单词出现的次数
}

struct Node {
    string word;
    int count;
};

vector<Node> ans;

// DFS 遍历字典树，按字典序提取所有单词
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

// 排序谓词：频率降序，频率相同则字典序升序
bool cmp(const Node &a, const Node &b) {
    if (a.count != b.count) return a.count > b.count;
    return a.word < b.word;
}

int main() {
    // 1. 打开文件
    ifstream infile("in.txt");
    if (!infile) return 0; // 若文件不存在则退出

    string temp = "";
    char c;
    
    // 2. 逐字符处理：仅处理字母，非字母视为分隔符
    while (infile.get(c)) {
        if (isalpha(c)) {
            temp += (char)tolower(c); // 转小写
        } else {
            if (!temp.empty()) {
                insert(temp); // 插入单词
                temp = "";
            }
        }
    }
    if (!temp.empty()) insert(temp); // 处理文件末尾最后一个单词
    infile.close();

    // 3. 从字典树中提取提取所有出现的单词
    dfs(0, "");

    // 4. 排序
    sort(ans.begin(), ans.end(), cmp);

    // 5. 输出前100个结果
    int total = ans.size();
    for (int i = 0; i < min(100, total); i++) {
        cout << ans[i].word << " " << ans[i].count << endl;
    }

    return 0;
}
