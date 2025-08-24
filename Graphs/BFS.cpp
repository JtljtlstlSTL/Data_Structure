BFS
/*广度优先搜索（BFS，Breadth-First Search）是一种图的遍历算法，它从一个起始节点开始，
首先访问该节点的所有邻接节点，然后再依次访问这些邻接节点的邻接节点，直到遍历完所有节点。
与深度优先搜索（DFS）不同，BFS采用“逐层”遍历的方式，
从而能够找到从起始节点到其他节点的最短路径（在无权图中）。*/

/*BFS的基本步骤：
选择起始节点：从图中的一个未访问的节点开始。
访问节点：访问当前节点并标记为已访问。
访问邻接节点：将当前节点的所有未访问的邻接节点加入队列。
队列处理：从队列中取出一个节点，重复步骤2和步骤3，直到队列为空。
结束条件：所有节点都被访问过，或者队列为空。*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 广度优先搜索BFS实现
void BFS(int start, vector<vector<int>>& graph) {
    int V = graph.size();  // 图中节点数
    vector<bool> visited(V, false);  // 用于记录节点是否被访问过
    queue<int> q;  // 用队列来管理待访问的节点

    // 将起始节点加入队列
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();  // 获取队列头部节点
        q.pop();  // 移除该节点

        // 访问当前节点
        cout << node << " ";

        // 遍历所有邻接节点
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;  // 标记为已访问
                q.push(neighbor);  // 将未访问的邻接节点加入队列
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

    cout << "BFS traversal starting from node 0:" << endl;
    BFS(0, graph);  // 从节点 0 开始进行 BFS

    return 0;
}

/*输出:
BFS traversal starting from node 0:
0 1 2 3 4 5 */
