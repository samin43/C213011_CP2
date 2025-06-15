#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int V, E;

    // Keep reading until V is 0
    while (scanf("%d", &V), V != 0) {
        scanf("%d", &E);

        // Create a graph with V vertices
        vector<vector<int>> graph(V);

        // Read all edges
        for (int i = 0; i < E; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // color[i] = -1 means vertex i is not colored yet
        vector<int> color(V, -1);
        color[0] = 0; // Start coloring vertex 0 with color 0

        queue<int> q;
        q.push(0);

        bool isBipartite = true;

        while (!q.empty() && isBipartite) {
            int u = q.front();
            q.pop();

            // Check all neighbors of u
            for (int v : graph[u]) {
                if (color[v] == -1) {
                    // Assign the opposite color to neighbor v
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    // Found same color on both ends of an edge -> not bipartite
                    isBipartite = false;
                    break;
                }
            }
        }

        if (isBipartite)
            printf("BICOLORABLE.\n");
        else
            printf("NOT BICOLORABLE.\n");
    }

    return 0;
}

