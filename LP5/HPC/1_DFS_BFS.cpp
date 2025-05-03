#include <bits/stdc++.h>
#include <omp.h>
#include <ctime> // For clock()
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v); // Undirected
    }

    void DFS(int startVertex) {
        vector<bool> visited(V, false);
        DFSUtil(startVertex, visited);
    }

    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";
        for (int n : adj[v]) {
            if (!visited[n])
                DFSUtil(n, visited);
        }
    }

    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex, visited);
    }

    void parallelDFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i) {
            int n = adj[v][i];
            if (!visited[n]) {
                #pragma omp critical
                {
                    if (!visited[n]) {
                        parallelDFSUtil(n, visited);
                    }
                }
            }
        }
    }

    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (int n : adj[v]) {
                if (!visited[n]) {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }

    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int size = q.size();
            vector<int> temp;

            #pragma omp parallel for shared(q, visited)
            for (int i = 0; i < size; ++i) {
                int v;

                #pragma omp critical
                {
                    if (!q.empty()) {
                        v = q.front();
                        q.pop();
                        cout << v << " ";
                    }
                }

                for (int n : adj[v]) {
                    if (!visited[n]) {
                        #pragma omp critical
                        {
                            if (!visited[n]) {
                                visited[n] = true;
                                temp.push_back(n);
                            }
                        }
                    }
                }
            }

            for (int n : temp)
                q.push(n);
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Graph g(V);
    cout << "Enter edges (format: u v):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    clock_t startTime, endTime;

    cout << "\n🔵 Sequential DFS: ";
    startTime = clock();
    g.DFS(start);
    endTime = clock();
    cout << "\n⏱ Time: " << 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC << " ms\n";

    cout << "\n🟢 Parallel DFS: ";
    startTime = clock();
    g.parallelDFS(start);
    endTime = clock();
    cout << "\n⏱ Time: " << 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC << " ms\n";

    cout << "\n🔵 Sequential BFS: ";
    startTime = clock();
    g.BFS(start);
    endTime = clock();
    cout << "\n⏱ Time: " << 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC << " ms\n";

    cout << "\n🟢 Parallel BFS: ";
    startTime = clock();
    g.parallelBFS(start);
    endTime = clock();
    cout << "\n⏱ Time: " << 1000.0 * (endTime - startTime) / CLOCKS_PER_SEC << " ms\n";

    return 0;
}
