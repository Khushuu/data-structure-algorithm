// You are given a list of words sorted lexicographically according to an unknown alien language. 
// You need to determine the order of characters in this alien language.
// Input
// A list of words sorted according to alien dictionary order.
// Each word consists of lowercase English letters.

// Output
// A string representing the lexicographical order of characters in the alien language.
// If the order is not possible, return an empty string "".

// Input: words = ["wrt","wrf","er","ett","rftt"]
// Output: "wertf"

// From the order:

// "wrt" → "wrf" → means 't' < 'f'.
// "wrf" → "er" → means 'w' < 'e'.
// "er" → "ett" → means 'r' < 't'.
// "ett" → "rftt" → means 'e' < 'r'.

// So, the correct character order is "wertf".

// Understanding the Problem
// The input list is sorted lexicographically.
// We must derive the relative order of characters from the words.
// Topological Sorting is used to find the order of characters.

// Approach: Graph + Topological Sorting (Kahn's Algorithm - BFS)

// Steps
// Build a Graph
// Treat each character as a node.
// Add directed edges based on order found in words[i] vs words[i+1].

// If words[i] is a prefix of words[i+1] but longer (apple vs app), return "".
// this is done since for correct order app should be before apple --> that is the right order
// if apple is before app that means no correct order is possible hence return ""

// Topological Sorting using Kahn's Algorithm (BFS)
// Use in-degree (number of incoming edges).
// Start from nodes with in-degree = 0.
// Process the nodes in BFS order.

// code
// BFS Solution - Kahn's algorithm

// Time Complexity
// Building the graph:
// Each edge corresponds to an adjacent word pair → O(C), where C is the total number of characters across all words.
// Topological sorting:
// O(V + E), where V is the number of unique characters (≤ 26), and E is the number of edges.
// Total Complexity: O(C + V + E) ≈ O(C).

// Space Complexity
// Graph storage: O(V + E).
// In-degree array: O(V).
// Queue storage: O(V).
// Total Complexity: O(V + E) ≈ O(C).

// --------------------------------------------------------------------------------------------------------
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> inDegree;
        
        // Step 1: Initialize the graph with all unique characters
        for (string& word : words) {
            for (char c : word) {
                inDegree[c] = 0; // Ensure all characters are in inDegree map
            }
        }

        // Step 2: Build the graph by comparing adjacent words
        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i], w2 = words[i + 1];
            int len = min(w1.size(), w2.size());

            // Invalid case: Prefix problem (apple, app)
            if (w1.size() > w2.size() && w1.substr(0, len) == w2.substr(0, len))
                return ""; 

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    if (!graph[w1[j]].count(w2[j])) { // Prevent duplicate edges
                        graph[w1[j]].insert(w2[j]);
                        inDegree[w2[j]]++; // Increase in-degree of w2[j]
                    }
                    break; // Only first different character matters
                }
            }
        }

        // Step 3: Topological Sort (BFS using Kahn's Algorithm)
        queue<char> q;
        string order;

        // Push all nodes with in-degree 0
        for (auto [ch, degree] : inDegree) {
            if (degree == 0) q.push(ch);
        }

        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            order += curr;

            for (char neighbor : graph[curr]) {
                if (--inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Step 4: If we processed all characters, return order, else return ""
        return order.size() == inDegree.size() ? order : "";
    }
};

// --------------------------------------------------------------------------------------------------------

// DFS solution 

// Build a Directed Graph
// Each unique character is a node.
// If word1[i] appears before word2[i], add an edge word1[i] → word2[i].
// If word1 is a prefix of word2 but longer (apple, app), return "".

// Detect Cycles & Perform Topological Sort using DFS
// Use a visited map with 3 states:
// 0 → Not visited
// 1 → Visiting (Gray) → Cycle detected
// 2 → Fully processed (Black)
// Cycle detection: If we encounter a node marked 1 (Visiting) during DFS, we have a cycle, return "".

// Postorder traversal ensures characters are added to the result in correct order.

// Time Complexity: O(C + V + E) ≈ O(C)
// Space Complexity: O(V + E) ≈ O(C) 
// --------------------------------------------------------------------------------------------------------

class Solution {
public:
    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, int> visited; // 0 = Not visited, 1 = Visiting, 2 = Processed
    string result;

    bool dfs(char node) {

        if (visited[node] == 1) return false; // Cycle detected
        if (visited[node] == 2) return true;  // Already processed

        visited[node] = 1; // Mark as Visiting

        for (char neighbor : graph[node]) {
            if (!dfs(neighbor)) return false; // If cycle detected in DFS, return false
        }

        visited[node] = 2; // Mark as Processed
        result += node;    // Add to result in postorder
        return true;
    }

    string alienOrder(vector<string>& words) {
        // Step 1: Initialize graph with all unique characters
        for (string& word : words) {
            for (char c : word) {
                graph[c] = {}; // Ensure all characters exist in graph
            }
        }

        // Step 2: Build the graph
        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i], w2 = words[i + 1];
            int len = min(w1.size(), w2.size());

            // Invalid case: "apple" → "app" (wrong order)
            if (w1.size() > w2.size() && w1.substr(0, len) == w2.substr(0, len))
                return ""; 

            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    graph[w1[j]].insert(w2[j]); // Add edge w1[j] → w2[j]
                    break; // Only first different character matters
                }
            }
        }

        // Step 3: Perform DFS on each character
        for (auto [ch, _] : graph) {
            if (visited[ch] == 0) { // If not visited
                if (!dfs(ch)) return ""; // Cycle detected
            }
        }

        reverse(result.begin(), result.end()); // Reverse postorder to get the correct order
        return result;
    }
};

// --------------------------------------------------------------------------------------------------------
