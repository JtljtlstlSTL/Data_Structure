//DFS
/*深度优先搜索（DFS，Depth-First Search）是一种图或树的遍历算法。
它从一个节点开始，沿着该节点的边向下访问，直到访问到叶子节点或没有更多未访问的节点为止，
然后回溯到上一个节点继续搜索，直到遍历完整个图或树。

DFS的基本步骤：
选择起始节点：从图中的一个未访问的节点开始。
访问该节点：访问当前节点并标记为已访问。
递归或栈式遍历邻接节点：对于当前节点的每一个邻接节点，如果该邻接节点没有被访问过，就继续访问它。重复这一过程，直到没有未访问的邻接节点。
回溯：当没有未访问的邻接节点时，回溯到上一个节点，继续对其他邻接节点进行遍历。
结束条件：直到所有节点都被访问过。*/

//1. 使用递归实现 DFS

#include <iostream>
#include <vector>
using namespace std;

// 深度优先搜索递归实现
void DFS(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    // 访问当前节点并标记为已访问
    visited[node] = true;
    cout << node << " ";

    // 遍历所有邻接节点
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            DFS(neighbor, graph, visited);  // 递归访问未访问的邻接节点
        }
    }
}

int main() {
    int V = 6;  // 图中节点数目
    vector<vector<int>> graph(V);  // 图的邻接表表示

    // 构建图
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(0);
    graph[1].push_back(3);
    graph[2].push_back(0);
    graph[2].push_back(4);
    graph[3].push_back(1);
    graph[4].push_back(2);
    graph[4].push_back(5);
    graph[5].push_back(4);

    vector<bool> visited(V, false);  // 用于记录节点是否被访问过

    cout << "DFS traversal using recursion:" << endl;
    DFS(0, graph, visited);  // 从节点 0 开始进行 DFS

    return 0;
}

//输出：
//DFS traversal using recursion:
//0 1 3 2 4 5 

//2. 使用栈实现 DFS

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 深度优先搜索栈实现
void DFS(int start, vector<vector<int>>& graph) {
    int V = graph.size();
    vector<bool> visited(V, false);  // 用于记录节点是否被访问过
    stack<int> s;

    s.push(start);  // 从起始节点入栈
    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;  // 访问当前节点
            cout << node << " ";

            // 遍历所有邻接节点，并将未访问的邻接节点压入栈
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}

int main() {
    int V = 6;  // 图中节点数目
    vector<vector<int>> graph(V);  // 图的邻接表表示

    // 构建图
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(0);
    graph[1].push_back(3);
    graph[2].push_back(0);
    graph[2].push_back(4);
    graph[3].push_back(1);
    graph[4].push_back(2);
    graph[4].push_back(5);
    graph[5].push_back(4);

    cout << "DFS traversal using stack:" << endl;
    DFS(0, graph);  // 从节点 0 开始进行 DFS

    return 0;
}

//输出：
//DFS traversal using stack:
//0 2 4 5 1 3 
