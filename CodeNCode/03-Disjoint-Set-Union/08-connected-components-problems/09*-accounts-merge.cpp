// 721. Accounts Merge
// VERY VERY VERY IMPORTANT PROBLEM

// # LeetCode 721. Accounts Merge

// This is one of the most important **Disjoint Set Union (DSU / Union-Find)** problems because it demonstrates how DSU can merge **objects that share a common attribute** rather than directly merging graph nodes.

// ---

// # Problem Statement

// You are given accounts like:

// ```text
// [
// ["John","johnsmith@mail.com","john_newyork@mail.com"],
// ["John","johnsmith@mail.com","john00@mail.com"],
// ["Mary","mary@mail.com"],
// ["John","johnnybravo@mail.com"]
// ]
// ```

// Each account consists of

// ```text
// [Name, Email1, Email2, Email3...]
// ```

// Two accounts belong to the same person if **they share at least one email**.

// Notice:

// The **name alone is NOT enough**.

// Example:

// ```text
// John
// john@gmail.com

// John
// abc@gmail.com
// ```

// These could be two different people.

// But

// ```text
// John
// john@gmail.com

// John
// john@gmail.com
// ```

// Definitely belong to the same person.

// ---

// # Expected Output

// ```text
// [
// ["John",
// "john00@mail.com",
// "john_newyork@mail.com",
// "johnsmith@mail.com"],

// ["Mary",
// "mary@mail.com"],

// ["John",
// "johnnybravo@mail.com"]
// ]
// ```

// Emails inside every account should be sorted.

// ---
class DSU {
    private:
        vector<int> parent;
        vector<int> size;

    public:
        // constructore
        DSU(int n) {

            parent.resize(n);
            size.resize(n);

            // each account is a parent of itself
            for(int i = 0; i < n; i++)
                parent[i] = i;
        }

        // find method with path compression
        int find(int a) {

            if(parent[a] == a) return a;
            return parent[a] = find(parent[a]);
        }

        // union by size - union is a reserved keyword in c++ hence we use unite name
        void unite(int a, int b) {

            int rootA = find(a);
            int rootB = find(b);

            if(rootA == rootB) return;

            if(size[rootA] < size[rootB])
                swap(rootA, rootB);
            
            parent[rootB] = rootA;
            size[rootA] += size[rootB];

            return;
        }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        
        // USING DSU
        // firstly we will map each email to its id 
        // if the email already is mapped to a group id 
        // we will merge the current group it lies in with the previous id 

        // secondly after the merge now we need to map each email directly with the parent id 
        // we will use find to find the parent of each email id 
        // an id will get mapped directly to the string of the emails

        // now the final task is to build the result
        // we will find the account name using id - push the account name first 
        // then push the list of strings 
        // also since we need the emails to be sorted we will sort the emails 
        // return result

        int n = accounts.size();
        unordered_map<string, int> emailToIndex;

        // initialize DSU
        DSU dsu(n);

        for(int i = 0; i < n; i++) {
            
            // index 0 is name so ignore it
            for(int j = 1; j < accounts[i].size(); j++) {
                
                string email = accounts[i][j];
                // if id does not exist map it else merge the group
                if(emailToIndex.count(email) == 0) 
                    emailToIndex[email] = i;
                else 
                    dsu.unite(i, emailToIndex[email]);
            }
        }

        // map each id directly to the parent index
        unordered_map<int, vector<string>> emailGroup;

        for(auto &[email, index]: emailToIndex) {

            int parent = dsu.find(index);
            emailGroup[parent].push_back(email);
        }

        // now form the result by looping over all parents
        vector<vector<string>> result;

        for (auto &[index, emails] : emailGroup) {

            // get account name from the index
            string accountName = accounts[index][0];
            result.push_back({accountName});

            // insert all emails
            result.back().insert(result.back().end(), emails.begin(), emails.end());

            // sort the emails (skip account name)
            sort(result.back().begin() + 1, result.back().end());
        }

        return result;
    }
};

// Complexity Analysis

// Here N is the number of accounts and K is the maximum length of an account.

// Time complexity: O(NKlogNK)

// While merging we consider the size of each connected component and we always choose the representative of the larger component to be the new representative of the smaller component, also we have included the path compression so the time complexity for find/union operation is α(N) (Here, α(N) is the inverse Ackermann function that grows so slowly, that it doesn't exceed 4 for all reasonable N (approximately N<10 ^600).

// We find the representative of all the emails, hence it will take O(NKα(N)) time. We are also sorting the components and the worst case will be when all emails end up belonging to the same component this will cost O(NK(logNK)).

// Hence the total time complexity is O(NK⋅logNK+NK⋅α(N)).

// Space complexity: O(NK)

// List representative, size store information corresponding to each group so will take O(N) space. All emails get stored in emailGroup and component hence space used is O(NK).

// The space complexity of the sorting algorithm depends on the implementation of each programming language. For instance, in Java, Collections.sort() dumps the specified list into an array this will take O(NK) space then Arrays.sort() for primitives is implemented as a variant of quicksort algorithm whose space complexity is O(logNK). In C++ sort() function provided by STL is a hybrid of Quick Sort, Heap Sort, and Insertion Sort with the worst-case space complexity of O(logNK).






