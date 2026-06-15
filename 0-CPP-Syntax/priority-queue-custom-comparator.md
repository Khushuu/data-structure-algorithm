This is one of the most confusing parts of `priority_queue` comparators.

Given:

```cpp
struct Compare {
    bool operator()(Node a, Node b) {

        if (a.frequency == b.frequency)
            return a.element < b.element;

        return a.frequency < b.frequency;
    }
};
```

**No, the smaller element will NOT come first.**

Because in a `priority_queue`, the comparator works in a somewhat reversed way:

```cpp
return true;
```

means:

```text
"a has lower priority than b"
```

---

### Let's test it

Suppose:

```cpp
a = {element=1, frequency=2}
b = {element=2, frequency=2}
```

Since frequencies are equal:

```cpp
return a.element < b.element;
```

becomes

```cpp
return 1 < 2; // true
```

# So the comparator says:

```text
1 has lower priority than 2
```

Therefore:

# IMPORTANT
```text
2 will be above 1 in the max heap
```

and will be popped first.

---

### Heap Order

Elements:

```text
(1, freq=2)
(2, freq=2)
(3, freq=2)
```

Using:

```cpp
if(a.frequency == b.frequency)
    return a.element < b.element;
```

Top of heap:

```text
3
then 2
then 1
```

So **larger element gets higher priority**.

---

### If you want smaller element first

Use:

```cpp
struct Compare {
    bool operator()(Node a, Node b) {

        if (a.frequency == b.frequency)
            return a.element > b.element;

        return a.frequency < b.frequency;
    }
};
```

Now for:

```cpp
a = 1
b = 2
```

we get:

```cpp
return 1 > 2; // false
```

and

```cpp
return 2 > 1; // true
```

meaning:

```text
2 has lower priority than 1
```

Thus heap order becomes:

```text
1
then 2
then 3
```

---

### Easy Rule to Remember

For a `priority_queue` comparator:

```cpp
return true;
```

means

```text
"Put a below b"
```

So:

```cpp
return a.element < b.element;
```

⇒ smaller element goes below larger element

⇒ **larger element comes first**

while

```cpp
return a.element > b.element;
```

⇒ larger element goes below smaller element

⇒ **smaller element comes first**.
