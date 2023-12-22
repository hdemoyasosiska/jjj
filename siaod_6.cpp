#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>

using namespace std;

// Структура для представления пути
struct Path {
    vector<int> path;
    int weight;
};

// Найти кратчайший путь с использованием алгоритма Дейкстры
void dijkstra(int src, int dest, int adjMatrix[8][8], vector<int>& dist, vector<int>& parent) {
    int V = 8;

    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < V; v++) {
            if (adjMatrix[u][v] && dist[u] != INT_MAX &&
                dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Удалить ребро из графа
void removeEdge(int u, int v, int adjMatrix[8][8]) {
    adjMatrix[u][v] = 0;
    adjMatrix[v][u] = 0;
}

// Найти k кратчайших путей из вершины a в вершину b
void yenKShortestPaths(int src, int dest, int k, int adjMatrix[8][8]) {
    int V = 8;

    vector<Path> kShortestPaths;

    for (int i = 0; i < k; i++) {
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1);

        dijkstra(src, dest, adjMatrix, dist, parent);

        if (dist[dest] == INT_MAX) {
            break; // Если путь не существует
        }

        // Восстановление пути
        vector<int> path;
        int cur = dest;
        while (cur != -1) {
            path.push_back(cur);
            cur = parent[cur];
        }
        reverse(path.begin(), path.end());

        // Добавление пути в результат
        kShortestPaths.push_back({path, dist[dest]});

        // Удаление ребра, чтобы найти следующий путь
        for (int j = 0; j < path.size() - 1; j++) {
            int u = path[j];
            int v = path[j + 1];
            removeEdge(u, v, adjMatrix);
        }
    }

    // Вывод результатов
    cout << "K Shortest Paths from " << src + 1 << " to " << dest + 1 << ":\n";
    for (const auto& path : kShortestPaths) {
        cout << "Path: ";
        for (int vertex : path.path) {
            cout << vertex + 1 << " ";
        }
        cout << "| Distance: " << path.weight << endl;
    }
}

void inputAdjacencyMatrix(int adjMatrix[8][8]) {
    cout << "Enter the adjacency matrix (8x8) row by row:\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> adjMatrix[i][j];
        }
    }
}

int main() {
    int graph[8][8] = {
            {0, 23, 12, 0, 0, 0, 0, 0},
            {23, 0, 25, 0, 22, 0, 0, 35},
            {12, 25, 0, 18, 0, 0, 0, 0},
            {0, 0, 18, 0, 0, 20, 0, 0},
            {0, 22, 0, 0, 0, 23, 14, 0},
            {0, 0, 0, 20, 23, 0, 24, 0},
            {0, 0, 0, 0, 14, 24, 0, 16},
            {0, 35, 0, 0, 0, 0, 16, 0},
    };

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;
    source--;

    int target;
    cout << "Enter the target vertex: ";
    cin >> target;
    target--;

    int k;
    cout << "Enter the value of k: ";
    cin >> k;

    yenKShortestPaths(source, target, k, graph);

    return 0;
}
