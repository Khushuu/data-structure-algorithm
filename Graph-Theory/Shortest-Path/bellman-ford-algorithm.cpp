// BELLMAN-FORD ALGORITHM 
// It is a dynamic programming algorithm
// It works by relaxing all edges up to n-1 times (where n is the number of nodes)

// It can handle negative weights and is used for graphs with negative weight edges
// It can also detect negative weight cycles

// In negative weight cycles, the distance to the node will keep decreasing indefinitely
// and the algorithm will not terminate

// FOR NEGATIVE WEIGHT CYCLES - SSSP can not be found 
// U can not find single source shortest path in a graph with negative weight cycles
// If there is a negative weight cycle reachable from the source, the algorithm will not terminate

// -------------------------------------------------------------------------------------------------------------------------
// Explanation

// 1. What is Bellman–Ford?
// The Bellman–Ford algorithm is used to find the shortest path from a single source to all vertices in a weighted graph.
// Unlike Dijkstra’s algorithm, Bellman–Ford:

// Works with negative weight edges (as long as there are no negative weight cycles reachable from the source)
// Can detect negative weight cycles

// ** Question: Why I said "as long as there are no negative weight cycles reachable from the source"
// Bellman–Ford will still run even if there’s a negative weight cycle.
// However:

// If the negative cycle is reachable from the source, there’s no finite shortest path — because you can loop around the cycle infinitely, reducing the cost forever.
// In that case, Bellman–Ford’s shortest path result is meaningless — it can’t return a well-defined “shortest” distance, because such a distance doesn’t exist.

// So the algorithm does two things:

// Find shortest paths (if possible)
// Detect negative weight cycles (so you know if your shortest paths are invalid)

// If a negative weight cycle exists somewhere else in the graph, but you can’t get to it from your starting point, then:
// You can’t use that cycle to reduce distances.
// The paths from your source remain well-defined.
// Bellman–Ford will still return correct shortest distances for all reachable nodes.

// Key takeaway
// Reachable negative cycle → shortest path doesn’t exist (distance → -∞) for at least some vertices.
// Unreachable negative cycle → harmless for shortest paths from the given source.

// -------------------------------------------------------------------------------------------------------------------------

// EDGE Relaxation
// A --> B
// dist[A] = a and dist[B] = b and weight (A -> B) = w

// a = distance of A from src
// b = distance of B from src
// w = distance b/w A and B

// newDist = dist[A] + w
// newDist = reaching B through A 

// if ( newDist < dist[B]) then dist[B] = newDist // RELAXATION
// only keep minimum possible distance to reach B

// -------------------------------------------------------------------------------------------------------------------------

// Time Complexity: O(V * E)
// Space Complexity: O(V)

// CODE 
// --------------------------------------------------------------------------------------------------------------------------



// --------------------------------------------------------------------------------------------------------------------------
