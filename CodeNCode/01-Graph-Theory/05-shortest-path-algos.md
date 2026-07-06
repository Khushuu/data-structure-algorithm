

## Shortest Path Algorithms Cheat Sheet

| Graph Type                   | Edge Weights                                         | Problem       | Algorithm                                                                                                       | Time Complexity    |
| ---------------------------- | ---------------------------------------------------- | ------------- | --------------------------------------------------------------------------------------------------------------- | ------------------ |
| Undirected                   | Unweighted                                           | Single Source | **BFS**                                                                                                         | **O(V + E)**       |
| Directed                     | Unweighted                                           | Single Source | **BFS**                                                                                                         | **O(V + E)**       |
| Undirected                   | Weighted (non-negative)                              | Single Source | **Dijkstra**                                                                                                    | **O((V+E) log V)** |
| Directed                     | Weighted (non-negative)                              | Single Source | **Dijkstra**                                                                                                    | **O((V+E) log V)** |
| Directed                     | Weighted (negative edges allowed, no negative cycle) | Single Source | **Bellman-Ford**                                                                                                | **O(VE)**          |
| Undirected                   | Weighted (negative edge)                             | Single Source | **Not applicable** (a negative edge immediately creates a negative cycle by traversing the edge back and forth) | —                  |
| Directed Acyclic Graph (DAG) | Weighted or Unweighted                               | Single Source | **Topological Sort + DP**                                                                                       | **O(V + E)**       |

---

# All-Pairs Shortest Path (APSP)

| Graph Type                                    | Edge Weights | Algorithm                  | Time Complexity      |
| --------------------------------------------- | ------------ | -------------------------- | -------------------- |
| Unweighted                                    | Any          | BFS from every vertex      | **O(V(V+E))**        |
| Weighted (non-negative)                       | Any          | Dijkstra from every vertex | **O(V(E log V))**    |
| Weighted (negative edges, no negative cycles) | Directed     | **Johnson's Algorithm**    | **O(VE + V² log V)** |
| Weighted                                      | Any          | **Floyd-Warshall**         | **O(V³)**            |

---

# Decision Tree

```text
Need shortest path?

│
├── Single Source?
│      │
│      ├── Unweighted?
│      │        └── BFS
│      │
│      ├── DAG?
│      │        └── Topological Sort
│      │
│      ├── Weighted (all edges ≥ 0)?
│      │        └── Dijkstra
│      │
│      └── Negative edges?
│               └── Bellman-Ford
│
└── All Pairs?
       │
       ├── Small graph (V ≤ 500)?
       │        └── Floyd-Warshall
       │
       ├── Sparse graph?
       │        ├── Unweighted → BFS from every node
       │        ├── Positive weights → Dijkstra from every node
       │        └── Negative weights → Johnson's Algorithm
```

----------------------------------------------------------------------------------------------------------

# When to use each algorithm

### 1. BFS

* Unweighted graph
* Directed or undirected
* Finds shortest path in terms of number of edges

Example:

```text
1--2--3
|
4
```

Shortest path:

```text
1 → 3 = 2 edges
```

----------------------------------------------------------------------------------------------------------

### 2. DFS

**Never** use DFS for shortest paths in a general graph.

Works only for:

* Trees (because there is a unique path)
* Special problems where the graph structure guarantees uniqueness

----------------------------------------------------------------------------------------------------------

### 3. Dijkstra

Conditions:

* Edge weights ≥ 0
* Directed or undirected

Example:

```text
A --5--> B
A --2--> C
C --1--> B
```

Shortest:

```text
A → C → B = 3
```

----------------------------------------------------------------------------------------------------------

### 4. Bellman-Ford

Use when:

* Negative edges exist
* Need to detect negative cycles

Example:

```text
A → B = 4
A → C = 5
C → B = -3
```

Shortest:

```text
A → C → B = 2
```

----------------------------------------------------------------------------------------------------------

### 5. Topological Sort (DAG)

Works only if graph has **no cycles**.

Even if weights are negative, it still works because vertices are processed in topological order.

Time:

```text
O(V+E)
```

Fastest algorithm for shortest paths in DAGs.

----------------------------------------------------------------------------------------------------------

### 6. Floyd-Warshall

Computes every pair shortest path.

Produces:

```text
dist[i][j]
```

for every pair `(i, j)`.

Works with:

* Directed
* Undirected
* Negative edges

Does **not** work if a negative cycle exists (distances are not well-defined).

Time:

```text
O(V³)
```

Space:

```text
O(V²)
```

----------------------------------------------------------------------------------------------------------

### 7. Johnson's Algorithm

Used for:

* Sparse graphs
* All-pairs shortest paths
* Negative edges
* No negative cycles

Steps:

1. Run Bellman-Ford once to compute vertex potentials.
2. Reweight all edges to eliminate negative weights.
3. Run Dijkstra from every vertex.
4. Convert distances back to original weights.

Time:

```text
O(VE + V² log V)
```

Much faster than Floyd-Warshall on large sparse graphs.

----------------------------------------------------------------------------------------------------------

# Interview Summary Table

| Algorithm        | Directed         | Undirected                                                                       | Unweighted | Positive Weights | Negative Weights                 | Detect Negative Cycle                   | Single Source | All Pairs                    |
| ---------------- | ---------------- | -------------------------------------------------------------------------------- | ---------- | ---------------- | -------------------------------- | --------------------------------------- | ------------- | ---------------------------- |
| DFS              | ✅ (not for SSSP) | ✅ (not for SSSP)                                                                 | ❌          | ❌                | ❌                                | ❌                                       | Tree only     | ❌                            |
| BFS              | ✅                | ✅                                                                                | ✅          | ❌                | ❌                                | ❌                                       | ✅             | By running from every vertex |
| Dijkstra         | ✅                | ✅                                                                                | ❌          | ✅                | ❌                                | ❌                                       | ✅             | By running from every vertex |
| Bellman-Ford     | ✅                | ⚠️ Rarely useful (negative edge implies a negative cycle in an undirected graph) | ❌          | ✅                | ✅                                | ✅                                       | ✅             | ❌                            |
| Topological Sort | ✅ (DAG only)     | N/A                                                                              | ✅          | ✅                | ✅                                | N/A                                     | ✅             | ❌                            |
| Floyd-Warshall   | ✅                | ✅                                                                                | ✅          | ✅                | ✅ (no negative cycles)           | Can detect by checking `dist[i][i] < 0` | ❌             | ✅                            |
| Johnson's        | ✅                | ✅ (typically with non-negative weights)                                          | ❌          | ✅                | ✅ (directed, no negative cycles) | Uses Bellman-Ford internally            | ❌             | ✅                            |


### Rule of thumb

* **Unweighted graph** → **BFS**
* **Weighted graph with non-negative weights** → **Dijkstra**
* **Negative edge weights** → **Bellman-Ford** (or **Topological Sort** if it's a DAG)
* **Need shortest paths between every pair** → **Floyd-Warshall** (dense/smaller graphs) or **Johnson's Algorithm** (sparse graphs with possible negative edges)
* **Tree** → A simple **DFS or BFS** computes single-source shortest distances because there is exactly one simple path between any two nodes.
