In C++, you can concatenate characters (`char`) to form a string (`std::string`) in several ways.

### 1. Append characters to a string

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s;

    char a = 'H';
    char b = 'i';

    s += a;
    s += b;

    std::cout << s;  // Output: Hi
}
```
############################################################################################################

### 2. Construct a string from characters

```cpp
#include <iostream>
#include <string>

int main() {
    char a = 'H';
    char b = 'i';

    std::string s;
    s.push_back(a);
    s.push_back(b);

    std::cout << s;  // Output: Hi
}
```
############################################################################################################

### 3. Concatenate characters in an expression

Since `char + char` performs integer addition (based on ASCII values), you need to convert at least one character to a string:

```cpp
char a = 'H';
char b = 'i';

std::string s = std::string(1, a) + b;

std::cout << s;  // Output: Hi
```

Or:

```cpp
std::string s = std::string() + a + b;
```

############################################################################################################

### Building a string in a loop

```cpp
std::string s;

for (char c : {'H', 'e', 'l', 'l', 'o'}) {
    s.push_back(c);
}

std::cout << s;  // Hello
```

`push_back()` and `operator+=` are the most common and efficient ways to build a string character by character.


############################################################################################################

### Common mistake

```cpp
char a = 'H';
char b = 'i';

auto x = a + b;  // x is an int (72 + 105 = 177), NOT "Hi"
```

############################################################################################################
