#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int V, E;

    while (scanf("%d", &V), V != 0) {
        scanf("%d", &E);

        vector<vector<int>> graph(V);

        for (int i = 0; i < E; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        vector<int> color(V, -1);
        color[0] = 0; 

        queue<int> q;
        q.push(0);

        bool isBipartite = true;

        while (!q.empty() && isBipartite) {
            int u = q.front();
            q.pop();

            // Check all neighbors of u
            for (int v : graph[u]) {
                if (color[v] == -1) {
                    
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
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

