// Problem: https://codeforces.com/problemset/problem/20/C

#include <bits/stdc++.h>
using namespace std;

// may not need ll if distance can fit in int
typedef long long ll;
typedef pair<int, ll> pill;
const ll INF = 1e18;

// returns shortest path
vector<int> dijkstra(int start, int num_of_nodes, vector<vector<pill> >& adj_list) {
    vector<ll>distance(num_of_nodes + 1, INF);
    vector<int>parent(num_of_nodes + 1, -1);

    distance[start] = 0;
    
    // least distant (closest) node comes first
    priority_queue<pill, vector<pill>, greater<pill> > queue_of_nodes;
    
    // (distance of node, node)
    queue_of_nodes.push(pill(0, start));
    
    while (!queue_of_nodes.empty()) {
        int cur_node = queue_of_nodes.top().second;
        ll cur_distance = queue_of_nodes.top().first;
        queue_of_nodes.pop();

        for (auto edge : adj_list[cur_node]) {
            int to_node = edge.first;
            ll to_node_weight = edge.second;

            if (distance[cur_node] + to_node_weight < distance[to_node]) {
                distance[to_node] = distance[cur_node] + to_node_weight;
                parent[to_node] = cur_node;
                queue_of_nodes.push(pill(distance[to_node], to_node));
            }
        }
    }

    return parent;
}

int main() {
    int num_of_nodes, num_of_edges;
    scanf("%d %d", &num_of_nodes, &num_of_edges);

    vector<vector<pill> >adj_list(num_of_nodes + 1);

    for (int index = 0; index < num_of_edges; index++) {
        int u_node, v_node, weight;
        scanf("%d %d %d", &u_node, &v_node, &weight);
        adj_list[u_node].push_back(pill(v_node, weight));
        adj_list[v_node].push_back(pill(u_node, weight));
    }

    vector<int> parent_path = dijkstra(1, num_of_nodes, adj_list);
    vector<int>reverse_path;

    int cur_node = num_of_nodes;

    if (parent_path[cur_node] == -1) {
        printf("-1\n");
    }
    else {
        while(cur_node != 1) {
            reverse_path.push_back(cur_node);
            cur_node = parent_path[cur_node];
        }

        reverse_path.push_back(cur_node);

        reverse(reverse_path.begin(), reverse_path.end());

        bool leading_space_flag = false;
        
        for (auto node : reverse_path) {
            printf(leading_space_flag ? " %d": "%d", node);
            leading_space_flag = true;
        }

        printf("\n");
    }

    return 0;
}

/*
Input:
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1

Output:
1 4 3 5

*/