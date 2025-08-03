#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int vertex_to;
    int weight;
};

struct CompareEdges {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; 
    }
};

vector<pair<int, int>> primsAlgorithm(int numVertices, const vector<vector<Edge>>& adj) {
    vector<int> minWeight(numVertices, INT_MAX);

    vector<int> parent(numVertices, -1);

    vector<bool> inMST(numVertices, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareEdges> pq;

    minWeight[0] = 0;
    pq.push({ 0, 0 });

    vector<pair<int, int>> mstEdges;

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;

        if (parent[u] != -1) {
            mstEdges.push_back({ parent[u], u });
        }

        for (const auto& edge : adj[u]) {
            int v = edge.vertex_to;
            int weight = edge.weight;

            if (!inMST[v] && weight < minWeight[v]) {
                minWeight[v] = weight;
                parent[v] = u;
                pq.push({ v, weight });
            }
        }
    }

    return mstEdges;
}

int main() {
    int numVertices = 7;

    vector<vector<Edge>> adj(numVertices);

    char vertices[7];
    for (int i = 0; i < 7; i++) {
        vertices[i] = 'a' + i;
    }
    vertices[6] = 'i';

    adj[0].push_back({ 1, 1 });
    adj[0].push_back({ 2, 5 });

    adj[1].push_back({ 0, 1 });
    adj[1].push_back({ 2, 4 });
    adj[1].push_back({ 3, 8 });
    adj[1].push_back({ 6, 7 });

    adj[2].push_back({ 0, 5 });
    adj[2].push_back({ 1, 4 });
    adj[2].push_back({ 3, 6 });
    adj[2].push_back({ 5, 2 });

    adj[3].push_back({ 1, 8 });
    adj[3].push_back({ 2, 6 });
    adj[3].push_back({ 5, 9 });
    adj[3].push_back({ 6, 11 });

    adj[4].push_back({ 5, 12 });
    adj[4].push_back({ 6, 10 });

    adj[5].push_back({ 2, 2 });
    adj[5].push_back({ 3, 9 });
    adj[5].push_back({ 4, 12 });
    adj[5].push_back({ 6, 3 });

    adj[6].push_back({ 1, 7 });
    adj[6].push_back({ 3, 11 });
    adj[6].push_back({ 4, 10 });
    adj[6].push_back({ 5, 3 });

    vector<pair<int, int>> mst = primsAlgorithm(numVertices, adj);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    int totalWeight = 0;
    for (const auto& edge : mst) {
        cout << "(" << vertices[edge.first] << ", " << vertices[edge.second] << "), ";
        for (const auto& neighbor : adj[edge.first]) {
            if (neighbor.vertex_to == edge.second) {
                cout << "weight = " << neighbor.weight << endl;
                totalWeight += neighbor.weight;
                break;
            }
        }
        for (const auto& neighbor : adj[edge.second]) {
            if (neighbor.vertex_to == edge.first) {
                break; 
            }
        }
    }

    cout << "Total weight of the MST: " << totalWeight << endl;

    return 0;
}