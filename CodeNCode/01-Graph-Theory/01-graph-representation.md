In C++, graphs are commonly represented in **three main ways**:

1. **Adjacency Matrix**
2. **Adjacency List** (most common)
3. **Edge List**

Let's use the following undirected graph as an example:

```
    0
   / \
  1---2
   \
    3
```

Edges:

```
(0,1)
(0,2)
(1,2)
(1,3)
```

---

# 1. Adjacency Matrix

A 2D array where:

* `matrix[i][j] = 1` if an edge exists
* `matrix[i][j] = 0` otherwise

### Matrix

|   | 0 | 1 | 2 | 3 |
| - | - | - | - | - |
| 0 | 0 | 1 | 1 | 0 |
| 1 | 1 | 0 | 1 | 1 |
| 2 | 1 | 1 | 0 | 0 |
| 3 | 0 | 1 | 0 | 0 |

### C++ Code

```cpp
#include <iostream>
using namespace std;

int main() {
    const int V = 4;

    int graph[V][V] = {
        {0,1,1,0},
        {1,0,1,1},
        {1,1,0,0},
        {0,1,0,0}
    };

    // Print matrix
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
}
```

### Complexity

* Space: **O(V²)**
* Edge lookup: **O(1)**
* Iterate neighbors: **O(V)**

**Best for:** Dense graphs.

* Traversal BFS or DFS: **O(V²)**
* Adding a new node is not easy

---------------------------------------------------------------------------------------------------------------------------

# 2. Adjacency List (Most Popular)

Each vertex stores a list of its neighbors.

### Representation

```
0 -> 1 2

1 -> 0 2 3

2 -> 0 1

3 -> 1
```

### C++ Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int V = 4;

    vector<vector<int>> graph(V);

    graph[0].push_back(1);
    graph[0].push_back(2);

    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[1].push_back(3);

    graph[2].push_back(0);
    graph[2].push_back(1);

    graph[3].push_back(1);

    // Print graph
    for(int i=0;i<V;i++){
        cout << i << " -> ";
        for(int neighbor : graph[i])
            cout << neighbor << " ";
        cout << endl;
    }
}
```

### Complexity

* Space: **O(V + E)**
* Edge lookup: **O(degree of vertex)**
* Iterate neighbors: **O(degree)**

**Best for:** Sparse graphs. This is the representation used in most graph algorithms like **BFS**, **DFS**, **Dijkstra**, and **Topological Sort**.

---

# 3. Edge List

Store only the edges.

### Representation

```
(0,1)
(0,2)
(1,2)
(1,3)
```

### C++ Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<pair<int,int>> edges;

    edges.push_back({0,1});
    edges.push_back({0,2});
    edges.push_back({1,2});
    edges.push_back({1,3});

    for(auto edge : edges){
        cout << edge.first << " "
             << edge.second << endl;
    }
}
```

### Complexity

* Space: **O(E)**
* Edge lookup: **O(E)**

**Best for:** Algorithms that process edges directly, such as **Kruskal's Minimum Spanning Tree** and **Bellman–Ford**.

---

# 4. Weighted Adjacency List

If edges have weights:

Example:

```
0 --5-- 1
 \      |
 2      3
  \     |
    2
```

### C++ Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {

    int V = 3;

    vector<vector<pair<int,int>>> graph(V);

    // destination, weight
    graph[0].push_back({1,5});
    graph[0].push_back({2,2});

    graph[1].push_back({0,5});
    graph[1].push_back({2,3});

    graph[2].push_back({0,2});
    graph[2].push_back({1,3});

    for(int i=0;i<V;i++){
        cout << i << " -> ";

        for(auto edge : graph[i]){
            cout << "("
                 << edge.first
                 << ", weight="
                 << edge.second
                 << ") ";
        }

        cout << endl;
    }
}
```

---

# 5. Weighted Edge List

Useful for algorithms like **Bellman–Ford**.

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Edge{
    int u, v, wt;
};

int main(){

    vector<Edge> edges = {
        {0,1,5},
        {0,2,2},
        {1,2,3}
    };

    for(auto e : edges){
        cout << e.u << " "
             << e.v << " "
             << e.wt << endl;
    }
}
```

---

# Summary

| Representation          | Space    | Edge Lookup | Best Use                          |
| ----------------------- | -------- | ----------- | --------------------------------- |
| Adjacency Matrix        | O(V²)    | O(1)        | Dense graphs                      |
| Adjacency List          | O(V + E) | O(degree)   | Sparse graphs, BFS, DFS, Dijkstra |
| Edge List               | O(E)     | O(E)        | Kruskal, Bellman–Ford             |
| Weighted Adjacency List | O(V + E) | O(degree)   | Weighted graph traversal          |
| Weighted Edge List      | O(E)     | O(E)        | Edge-based weighted algorithms    |

### Which one should you use?

* **Adjacency List**: The default choice for most graph problems.
* **Adjacency Matrix**: When the graph is dense or you need constant-time edge existence checks.
* **Edge List**: When algorithms primarily iterate over edges rather than neighbors.
