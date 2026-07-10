// Union method for Disjoint Set Union (DSU)

// Why is union by rank required?

// The main benefit of union by rank or union by size is that they keep the DSU trees shallow, making `find()` operations much faster.

// ### Without union by rank/size

// Suppose you perform these unions:

// union(1,2)
// union(2,3)
// union(3,4)
// union(4,5)

// If you always make the second root point to the first (or vice versa), you can end up with a chain:


// 1
// |
// 2
// |
// 3
// |
// 4
// |
// 5

// Now,

// find(5);

// must traverse:

// 5 → 4 → 3 → 2 → 1

// Time complexity: O(n) in the worst case.

//------------------------------------------------------------------------------------------------

// ### With union by size

// Each tree stores the number of nodes it contains. The smaller tree is always attached under the larger tree.

// Example:

// Tree A (size = 8)

//       1
//     / | \
//    2  3  4
//       |
//       5

// Tree B (size = 2)

//    6
//    |
//    7

// Instead of making the large tree a child of the small tree, you do:


//       1
//     / | | \
//    2  3 4  6
//       |     |
//       5     7


// The height barely increases.

//------------------------------------------------------------------------------------------------

// ### With union by rank

// Instead of storing the size, you store an estimate of the tree's height (the rank).

// * Attach the tree with the smaller rank under the one with the larger rank.
// * If the ranks are equal, choose one as the new root and increment its rank by 1.

// This also keeps trees shallow.

//------------------------------------------------------------------------------------------------

// ### Why shallow trees matter

// The `find()` operation follows parent pointers until it reaches the root.

// If the tree height is:

// * 1000 → `find()` may need 1000 parent traversals.
// * 10 → `find()` needs at most 10 traversals.

// So the shorter the tree, the faster every `find()` becomes.

// //------------------------------------------------------------------------------------------------

// ### Complexity comparison

// | Implementation                        | Worst-case `find()`                          |
// | ------------------------------------- | -------------------------------------------- |
// | No optimization                       | O(n)                                     |
// | Union by rank only                    | O(log n)                                 |
// | Union by size only                    | O(log n)                                 |
// | Path compression only                 | Nearly O(log n) amortized                |
// | Union by rank/size + path compression | O(α(n)) amortized (effectively constant) |

// //------------------------------------------------------------------------------------------------

// ### Intuition

// Imagine merging companies:

// * Without union by size: A company with 10,000 employees could be made a subsidiary of a company with 2 employees, creating an unnecessarily deep management hierarchy.
// * With union by size: The 2-employee company becomes a subsidiary of the 10,000-employee company, keeping the hierarchy flatter.

// The same idea applies to DSU trees: attaching the smaller tree under the larger (or shorter under taller) prevents deep chains from forming, which makes future `find()` operations much faster.


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


// Basic union operation without optimizations. 
// Find the parent of both the sets
// Make parent of one set point to the parent of the other set.
// It merges the sets containing elements a and b by making the root of one set point to the root of the other set.

// This simply makes the root of one set the parent of the other.

void union(int a, int b) {

    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB)
        return;   // Already in the same set

    parent[rootB] = rootA;
}

// ------------------------------------------------------------------------------------------------ 

// Union by Rank
// The idea is to attach the shorter tree under the taller tree to keep the height small.
// The rank of the root is the height of the tree.

// Initialization: rank[root] = 0 for all roots.

vector<int> parent, rank;

DSU(int n) {
    parent.resize(n + 1);
    rank.assign(n + 1, 0);

    for (int i = 0; i <= n; i++)
        parent[i] = i;
}

// Here, rank[i] is an estimate of the height of the tree rooted at i.

// Implementation of union by rank:

// Rank is the height of the tree
// So to keep the tree balanced and keep the height small, we attach the smaller tree under the larger tree.
// The set with higher rank will become the parent of the set with lower rank. 
//If both sets have the same rank, we can choose either one as the new root and increment its rank by 1.

void union(int a, int b) {

    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB)
        return;

    // Parent with higher rank becomes the parent of the other 
    // rootB becomes the parent of rootA
    if (rank[rootA] < rank[rootB]) {
        parent[rootA] = rootB;
    }
    // rootA has higher rank than rootB, so rootA becomes the parent of rootB
    else if (rank[rootA] > rank[rootB]) {
        parent[rootB] = rootA;
    }
    // increase the rank of the root that becomes the parent by 1
    else {
        parent[rootB] = rootA;
        rank[rootA]++;
    }
}

// ------------------------------------------------------------------------------------------------ 

// Union by Size
// Better than union by rank
// Also gives additional info about the size of each set

// Instead of rank, we can use size to merge smaller trees under larger ones.

// Merging smaller trees into larger ones prevents unnecessary height growth.
// Works similarly to union by rank but is often simpler.

// Size is the number of elements in the set
// Size is initialized to 1 for each node.

void unionSet(int x, int y) {

    int rootX = find(x);
    int rootY = find(y);
	
    if(rootX == rootY) return; // Already in the same set

    // the one with bigger size will become the parent of the other 
    // size of rootX is greater than size of rootY, so rootX becomes the parent of rootY
    if (size[rootX] > size[rootY]) {
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    } else {
        parent[rootX] = rootY;
        size[rootY] += size[rootX];
    }
}

// ------------------------------------------------------------------------------------------------ 

// Union by Size (Cleaner Implementation)

// Even cleaner union by size implementation using swap() to avoid code duplication:
// always make rootX the larger set, and rootY the smaller set. 
// This way, we can avoid duplicating the code for updating the parent and size.

// and will always make rootX the parent of rootY, and update the size of rootX accordingly.

void unionSet(int x, int y) {

    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
        return; // Already in the same set

    // Ensure rootX is the larger set
    if (size[rootX] < size[rootY])
        swap(rootX, rootY);

    parent[rootY] = rootX;
    size[rootX] += size[rootY];
}

// ------------------------------------------------------------------------------------------------ 
