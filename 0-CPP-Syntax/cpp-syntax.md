
# C++ Syntax Cheatsheet

## Reverse sort methods in C++

### Using `std::greater`
```cpp
sort(v.begin(), v.end(), std::greater<int>());
```

### Using reverse iterators (clean)
```cpp
sort(v.rbegin(), v.rend());
```

### Using custom sort — lambda
```cpp
std::sort(v.begin(), v.end(), [](int a, int b) {
    return a > b; // descending order
});
```

### For vector of pairs
```cpp
std::sort(v.begin(), v.end(), [](auto &a, auto &b) {
    return a.first > b.first;
});
```

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

## Queue — FIFO (First In First Out)

Include and declaration:

```cpp
#include <queue>
std::queue<int> q;
```

Diagram: Front --> 1 2 3 4 <-- Back

### Operations

1. `push()` — inserts an element to the back of the queue

```cpp
q.push(1);
```

Time complexity: O(1)

2. `pop()` — removes the first element from the queue (does not return it)

```cpp
q.pop();
```

Time complexity: O(1)

3. `front()` — returns the first element

```cpp
q.front();
```

Time complexity: O(1)

4. `back()` — returns the last element

```cpp
q.back();
```

Time complexity: O(1)

5. `empty()` — checks if the queue is empty

```cpp
q.empty();
```

Time complexity: O(1)

6. `size()` — returns number of elements

```cpp
q.size();
```

Time complexity: O(1)

### Traversal example

```cpp
while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
}
```

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

## Hashmap — `std::unordered_map`

Stores key-value pairs using a hash table; unordered (not sorted).

Include and declaration:

```cpp
#include <unordered_map>
std::unordered_map<int, std::string> mp;
```

### Insertion

Method 1 — using `operator[]` (may create default value if key absent)

```cpp
mp[1] = 10;
mp[2] = 20;
```

Time complexity: average O(1)

Method 2 — using `insert`

```cpp
mp.insert({3, 30});
// or
mp.insert(std::make_pair(3, 30));
```

### Access

```cpp
std::cout << mp[1]; // prints 10
```

Note: `mp[100]` will insert `100` with a default value if it doesn't exist.

### Search — `find()`

```cpp
auto it = mp.find(2);
if (it != mp.end()) {
    std::cout << "Found";
    std::cout << it->first;  // key
    std::cout << it->second; // value
}
```

Time complexity: average O(1)

### Check existence — `count()`

```cpp
if (mp.count(5)) {
    std::cout << "Exists";
}
```

Returns `1` if present, `0` if absent. Average complexity O(1).

### Deletion

Erase by key:

```cpp
mp.erase(2);
```

Erase by iterator:

```cpp
auto it = mp.find(2);
if (it != mp.end()) mp.erase(it);
```

Average complexity: O(1)

### Size / Empty / Clear

```cpp
mp.size();   // average O(1)
mp.empty();  // average O(1)
mp.clear();  // O(n) // cleares everything
```

### Traversing 

# Method 1: Range-Based Loop (Most Common)

```cpp
for(auto &p : mp)
{
    cout << p.first << " "
         << p.second << endl;
}
```

# Complexity: O(n)

# Method 2: Iterator

```cpp
for(auto it = mp.begin();
    it != mp.end();
    ++it)
{
    cout << it->first << " "
         << it->second << endl;
}
```
# Complexity: O(n)

# Method 3: Structured Bindings (C++17)

Very clean.

```cpp
// what i prefer

for(auto &[key, value] : mp)
{
    cout << key << " "
         << value << endl;
}
```
# Complexity: O(n)

### IMPORTANT

```cpp

mp[key]++
mp[key]--
mp.find(key)
mp.count(key)
mp.erase(key)

for(auto &[k,v] : mp)

```

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------


// MIN and MAX element 

```cpp
// Returns iterators to the elements.

vector<int> v = {10, 5, 20, 8, 15};

int minElement = *min_element(v.begin(), v.end());
int maxElement = *max_element(v.begin(), v.end());


// min max element in a single pass
auto p = minmax_element(v.begin(), v.end());

cout << "Minimum element: " << *p.first << endl;
cout << "Maximum element: " << *p.second << endl;

// For arrays

int arr[] = {4, 2, 9, 1, 7};

int mx = *max_element(arr, arr + 5);
int mn = *min_element(arr, arr + 5);

```
