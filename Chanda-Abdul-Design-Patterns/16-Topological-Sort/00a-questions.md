Here are the **most popular and interview-favorite LeetCode problems** on **Topological Sort**, ordered from easiest to hardest.

| LeetCode | Problem                                       | Difficulty | Key Idea                                    |
| -------- | --------------------------------------------- | ---------- | ------------------------------------------- |
| **207**  | Course Schedule                               | Medium     | Basic Kahn's Algorithm / cycle detection    |
| **210**  | Course Schedule II                            | Medium     | Return topological ordering                 |
| **269**  | Alien Dictionary                              | Hard       | Build graph from words + topological sort   |
| **444**  | Sequence Reconstruction                       | Medium     | Unique topological ordering                 |
| **851**  | Loud and Rich                                 | Medium     | Topological sort + DP propagation           |
| **1203** | Sort Items by Groups Respecting Dependencies  | Hard       | Two-level topological sort                  |
| **1462** | Course Schedule IV                            | Medium     | Topological sort + transitive reachability  |
| **2115** | Find All Possible Recipes from Given Supplies | Medium     | Kahn's algorithm on dependency graph        |
| **2392** | Build a Matrix With Conditions                | Hard       | Two independent topological sorts           |
| **310**  | Minimum Height Trees                          | Medium     | Reverse topological process (leaf trimming) |
| **802**  | Find Eventual Safe States                     | Medium     | Reverse graph + topological sort            |
| **1857** | Largest Color Value in a Directed Graph       | Hard       | Topological sort + DP                       |
| **2050** | Parallel Courses III                          | Hard       | Topological sort + longest path DP          |
| **1136** | Parallel Courses *(Premium)*                  | Medium     | Level-order topological sort                |
| **1494** | Parallel Courses II *(Premium)*               | Hard       | Topological sort + Bitmask DP               |

---

# Must-Do Problems (Interview Preparation)

If you're preparing for coding interviews, these are the highest priority:

### ⭐ Easy Starter

* 207. Course Schedule
* 210. Course Schedule II

These teach:

* indegree
* queue
* cycle detection
* topological ordering

---

### ⭐ Intermediate

* 2115. Find All Possible Recipes from Given Supplies
* 851. Loud and Rich
* 1462. Course Schedule IV
* 802. Find Eventual Safe States

These introduce:

* propagation of information
* reverse graphs
* dependency resolution
* DAG DP

---

### ⭐ Advanced

* 269. Alien Dictionary
* 1857. Largest Color Value in a Directed Graph
* 2050. Parallel Courses III
* 2392. Build a Matrix With Conditions
* 1203. Sort Items by Groups Respecting Dependencies

These combine topological sorting with:

* dynamic programming
* graph construction
* multiple DAGs
* longest path
* grouping and scheduling

---

# Common Patterns

### 1. Cycle Detection

Problems:

* 207
* 210
* 269

Pattern:

```cpp
Build graph
↓
Compute indegree
↓
Push indegree 0 nodes
↓
Process queue
↓
If processed nodes != n → cycle exists
```

---

### 2. Dependency Resolution

Problems:

* 2115
* 1203
* 2392

Pattern:

```
Unlock nodes when prerequisites are completed.
```

---

### 3. DP on DAG

Problems:

* 851
* 1857
* 2050

Pattern:

```
Topo order
↓
Propagate DP values along edges
```

---

### 4. Reverse Topological Sort

Problems:

* 310
* 802

Pattern:

```
Reverse graph
↓
Start from terminal/leaf nodes
↓
Remove them layer by layer
```

---

### 5. Unique Ordering

Problems:

* 444
* 269

Pattern:

```
If queue size > 1 at any step,
multiple valid topological orders exist.
```

---

## Recommended Learning Order

1. **207. Course Schedule**
2. **210. Course Schedule II**
3. **2115. Find All Possible Recipes from Given Supplies**
4. **851. Loud and Rich**
5. **802. Find Eventual Safe States**
6. **1462. Course Schedule IV**
7. **269. Alien Dictionary**
8. **2050. Parallel Courses III**
9. **1857. Largest Color Value in a Directed Graph**
10. **2392. Build a Matrix With Conditions**
11. **1203. Sort Items by Groups Respecting Dependencies**

This sequence builds from the fundamentals of Kahn's algorithm to more advanced applications involving dynamic programming and complex dependency graphs.
