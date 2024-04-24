#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int start_node) {
    stack<int> s{{start_node}};

    while (!s.empty()) {
        int curr_node = s.top();
        s.pop();

        if (!visited[curr_node]) {
            visited[curr_node] = true;
            cout << curr_node << " ";

            #pragma omp parallel for
            for (int adj_node : graph[curr_node]) {
                if (!visited[adj_node]) {
                    s.push(adj_node);
                }
            }
        }
    }
}

int main() {
    int n, m, start_node;
    cout << "Enter the number of nodes, edges, and start node: ";
    cin >> n >> m >> start_node;

    cout << "Enter the pairs of edges:\n";
    for (int i = 0, u, v; i < m && cin >> u >> v; i++) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    cout << "Depth First Traversal starting from node " << start_node << ": ";
    dfs(start_node);
    cout << endl;

    return 0;
}
