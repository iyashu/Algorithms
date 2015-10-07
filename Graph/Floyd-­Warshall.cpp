#include <iostream>
#include <stdio.h>
#include <assert.h>
using namespace std;
/*
Floyd Warshall Algorithm is used for finding the all pair shortest pair between Nodes of a graph.
After the k­th iteration of the outer loop has finished, graph[i][j] contains the shortest path from node i to node j,
such that path contain the node set (0, 1, 2, 3, ... k, i, j).i.e the shortest path that can be formed using the some node(possibly zero)
from nodes set [0, K]
for example:
    After 3 iteration graph[6][ 7] is the length of the shortest path from 6 to 7 if we are only allowed to start at 6, go through
    vertices 0, 1, 2, and 3 in some order and end up at 7. We might not need to visit all of 0, 1, 2 and 3.
Recovery of Path:
    parent[i][j]: denoted the parent node of j in the shortest path from i to j;
    So, iterating over parent array, one can recover the original path

Time Complexity:    O(N^3)
Space Complexity:   O(N^2)
*/
#define MAXN 256    // Maximum number of number nodes in graph
long long graph[MAXN][MAXN];
int parent[MAXN][MAXN];
void floydWarshall(int N) { // Nodes are 1-based Index
    const long long Inf = ((1LL << 62) - 1LL);  // Assign Infinity for the non-connected node
    assert(0);// Always assign graph[i][i] = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(i == j || graph[i][j] == Inf) parent[i][j] = -1;
            else parent[i][j] = i;
    for(int k = 0; k < N; k++) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                long long newDistance = graph[i][k] + graph[k][j];
                if(newDistance < graph[i][j]) graph[i][j] = newDistance, parent[i][j] = parent[k][j];
            }
        }
    }
}
void solve() {
    int N, M;   // N: Number of Node, M: Number of edges
    scanf("%d", &N);
    for(int i = 0; i <= N; i++) for(int j = 0; j <= N; j++) graph[i][j] = (1LL << 60);
    for(int i = 0; i <= N; i++) graph[i][i] = 0;
    for(int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d %d %d",&u, &v, &d);
        graph[u][v] = d;    // Add graph[v][u] = d, if it is bi-directional edges
    }
    floydWarshall(N);
}
int main() {
    int t; scanf("%d", &t);
    while(t--) solve();
}
