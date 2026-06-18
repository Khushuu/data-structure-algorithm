# Identification

- sorted array or matrix
- high chance of Binary Search 

# Questions

- Order agnostic Binary Search
- First and Last occurence of an element
- Count of element in a sorted array
- **Number of times array is rotated** - **Important**
- **Find an element in rotated sorted array** - **Important**
- Searching in nearly sorted array
- Floor/Ceil of an element
- Next letter
- Index of last 1 in sorted array
- Find the position of an element in the infinite sorted array
- Minimum difference element in a sorted array

- Bitonic array maximum element
- Search in bitonic array 
- **Search in a row-wise and column-wise sorted matrix** - **Important**
- Find element in the sorted array that appears only once 
- Allocate minimum number of pages 

-------------------------------------------------------------------------------------------------------------------

In C++, the STL provides several binary-search-related algorithms in the `<algorithm>` header. 
They all work on **sorted ranges** (unless otherwise noted).

## 1. `binary_search()`

Checks whether a value exists in a sorted range.

### Syntax

```cpp
bool found = binary_search(v.begin(), v.end(), x);
```

### Returns

* `true` → element exists
* `false` → element does not exist

### Example

```cpp
vector<int> v = {1, 3, 5, 7, 9};

cout << binary_search(v.begin(), v.end(), 5); // 1
cout << binary_search(v.begin(), v.end(), 6); // 0
```

### When to use

When you **only need to know whether an element is present**, not its position.

-------------------------------------------------------------------------------------------------------------------

## 2. `lower_bound()`

# Finds the first element **greater than or equal to** the target.

### Syntax

```cpp
auto it = lower_bound(v.begin(), v.end(), x);
```

### Returns

Iterator pointing to:

* First element `>= x`
* `v.end()` if no such element exists

### Example

```cpp
vector<int> v = {1, 3, 3, 3, 5, 7};

auto it = lower_bound(v.begin(), v.end(), 3);

cout << (it - v.begin()); // 1
```

For a missing value:

```cpp
auto it = lower_bound(v.begin(), v.end(), 4);

cout << *it; // 5
```

### When to use

* Find insertion position while maintaining sorted order.
* Find first occurrence of duplicates.
* Count frequencies together with `upper_bound()`.

-------------------------------------------------------------------------------------------------------------------

## 3. `upper_bound()`

# Finds the first element **strictly greater than** the target.

### Syntax

```cpp
auto it = upper_bound(v.begin(), v.end(), x);
```

### Returns

Iterator pointing to:

* First element `> x`
* `v.end()` if no such element exists

### Example

```cpp
vector<int> v = {1, 3, 3, 3, 5, 7};

auto it = upper_bound(v.begin(), v.end(), 3);

cout << (it - v.begin()); // 4
```

### When to use
# NOTE:

* Find the position after the last occurrence.
* Count duplicates.

# IMPORTANT
```cpp
int cnt = upper_bound(v.begin(), v.end(), 3)
        - lower_bound(v.begin(), v.end(), 3);
```

Result:

```cpp
cnt = 3
```

-------------------------------------------------------------------------------------------------------------------

## 4. `equal_range()`

### Purpose

Gets both `lower_bound()` and `upper_bound()` in one call.

### Syntax

```cpp
auto p = equal_range(v.begin(), v.end(), x);
```

### Returns

A `pair<iterator, iterator>`:

```cpp
{lower_bound(...), upper_bound(...)}
```

### Example

```cpp
vector<int> v = {1, 3, 3, 3, 5, 7};

auto p = equal_range(v.begin(), v.end(), 3);

cout << p.first - v.begin();  // 1
cout << p.second - v.begin(); // 4
```

### When to use

When you need both bounds (common for duplicate counting).

---

# Visual Example

Array:

```text
Index: 0 1 2 3 4 5
Value: 1 3 3 3 5 7
```

Searching for `3`:

```text
lower_bound(3)
      ↓
1 3 3 3 5 7
  ^

upper_bound(3)
            ↓
1 3 3 3 5 7
        ^
```

* `lower_bound` → index `1`
* `upper_bound` → index `4`
* Count = `4 - 1 = 3`

-------------------------------------------------------------------------------------------------------------------

# Common Interview Patterns

### Check existence

```cpp
if (binary_search(v.begin(), v.end(), x))
```

or

```cpp
auto it = lower_bound(v.begin(), v.end(), x);
if (it != v.end() && *it == x)
```

---

### First occurrence

```cpp
auto it = lower_bound(v.begin(), v.end(), x);
```

---

### Last occurrence

```cpp
auto it = upper_bound(v.begin(), v.end(), x);
--it; // subtract one position
```

(Be careful that `x` actually exists.)

---

### Count occurrences

```cpp
int count =
    upper_bound(v.begin(), v.end(), x) -
    lower_bound(v.begin(), v.end(), x);
```

---

### Insert while keeping sorted order

```cpp
auto pos = lower_bound(v.begin(), v.end(), x);
v.insert(pos, x);
```

---

# Summary Table

| Function          | Returns                    | Meaning                     |
| ----------------- | -------------------------- | --------------------------- |
| `binary_search()` | `bool`                     | Whether value exists        |
| `lower_bound()`   | iterator                   | First element `>= x`        |
| `upper_bound()`   | iterator                   | First element `> x`         |
| `equal_range()`   | `pair<iterator, iterator>` | Both lower and upper bounds |

### Easy memory trick

* **lower** = first place where `x` can go without violating order (`>= x`)
* **upper** = first place after all `x`s (`> x`)
* **binary_search** = yes/no answer
* **equal_range** = both bounds together

All of these run in **O(log n)** time on sorted ranges.
