# What is Topological Sorting?

Topological Sorting is a **linear ordering of the vertices of a Directed Acyclic Graph (DAG)** such that for 
every directed edge:

```
u → v
```

vertex **u appears before v** in the ordering.

Topological Sort is used to find a linear ordering of elements that have dependencies on each other. 
For example, if event B is dependent on event A, A comes before B in topological ordering.

In simple words:

> If one task depends on another task, then the dependency must come first.

---------------------------------------------------------------------------------------------------------

# The basic idea behind the topological sort is to provide a partial ordering among the vertices of the graph such that if there is an edge from U to V then U≤V i.e., U comes before V in the ordering.

Here are a few fundamental concepts related to topological sort:

# Source: Any node that has no incoming edge and has only outgoing edges is called a source.
# Sink: Any node that has only incoming edges and no outgoing edge is called a sink.

So, we can say that a topological ordering starts with one of the sources and ends at one of the sinks.

* A topological ordering is possible only when the graph has **no directed cycles**, i.e. if the graph is a **Directed Acyclic Graph (DAG)**. 
* If the graph has a cycle, some vertices will have cyclic dependencies which makes it impossible to find a linear ordering among vertices.

# Kahn's Algorithm

* To find the topological sort of a graph we can traverse the graph in a Breadth First Search (BFS) way.
* We will start with all the sources, and in a stepwise fashion, save all sources to a sorted list. 
* We will then remove all sources and their edges from the graph. 
* After the removal of the edges, we will have new sources, so we will repeat the above process until all vertices are visited.

---------------------------------------------------------------------------------------------------------

Yes. **Topological sorting is possible for a disconnected Directed Acyclic Graph (DAG).**

A disconnected DAG is simply a graph with multiple connected components, each of which is acyclic. A topological ordering can include vertices from all components in any order that respects the edge constraints within each component.

### Example

```
Component 1:     0 → 1

Component 2:     2 → 3
```

One valid topological ordering is:

```
0 1 2 3
```

Another valid ordering is:

```
2 3 0 1
```

Another is:

```
0 2 1 3
```

All are correct because:

* `0` appears before `1`
* `2` appears before `3`

There is **no dependency** between the two components.

---

### How Kahn's Algorithm handles it

Initially, all nodes with **indegree = 0** are pushed into the queue.

For the above graph:

```
Indegree:
0 -> 0
1 -> 1
2 -> 0
3 -> 1

Queue = [0, 2]
```

The algorithm processes whichever zero-indegree node comes first, eventually visiting every component.

---

### How DFS handles it

With DFS, you simply start DFS from every unvisited vertex:

```cpp
for (int i = 0; i < V; i++) {
    if (!visited[i])
        dfs(i);
}
```

This ensures every disconnected component is covered.

---

### Key Point

* ✅ Connected DAG → Topological sort exists.
* ✅ Disconnected DAG → Topological sort also exists.
* ❌ Any graph containing a **cycle** → Topological sort does **not** exist.

---------------------------------------------------------------------------------------------------------


## Example

Suppose we have the graph:

```
0 → 1
↓
2 → 3
```

Edges:

```
0 → 1
0 → 2
2 → 3
```

A valid topological ordering is:

```
0 2 3 1
```

Another valid ordering is:

```
0 1 2 3
```

Notice:

* 0 comes before 1 ✅
* 0 comes before 2 ✅
* 2 comes before 3 ✅

There can be **multiple valid topological orderings**.

---------------------------------------------------------------------------------------------------------

# Where is Topological Sorting Used?

* Course Schedule (LeetCode 207)
* Course Schedule II (LeetCode 210)
* Task Scheduling
* Build Systems (compile dependencies)
* Package Managers (npm, Maven)
* Detecting Cycles in Directed Graphs

---------------------------------------------------------------------------------------------------------

# Can Every Graph Have a Topological Sort?

**No.**

Only **Directed Acyclic Graphs (DAGs)**.

Example:

```
0 → 1
↑   ↓
└── 2
```

This graph contains a cycle.
No topological ordering exists.