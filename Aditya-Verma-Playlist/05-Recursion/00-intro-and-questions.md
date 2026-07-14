## Recursion

* set of choices and decisions u make
* have a base condition for when to stop any futher processing 

-- create recursive tree - what choices we have -- what decisions we r making on it
-- just replicate the tree in code 

# ------------------------------------------------------------------------------------------------

# Method for solving recursion problems

**Induction - Hypothesis - Base Condition** 

# ------------------------------------------------------------------------------------------------

Example:

# Print 1 to n using a recursive function


void print(int n) {

	if(n == 0) return; // base condition

	print(n - 1); // induction 

	cout << n << " "; // hypothesis
}


// call stack 
let n = 4
print(4) --> print(3) --> print(2) --> print(1) --> print(0) --> 
pop print(0) --> 1 --> pop print(1) --> 2 --> pop print(2) --> 3 --> pop print(3) --> 4 --> pop print(4);

# ------------------------------------------------------------------------------------------------

# Print n to 1 using a recursive function

// write the print statement before making print(n - 1) call 


void print(int n) {

	if(n == 0) return; // base condition

	cout << n << " "; // hypothesis

	print(n - 1); // induction 
}

# ------------------------------------------------------------------------------------------------

# return n! - factorial of n using recursive function

int factorial(int n) {

	if(n == 0) return 1;

	return n * factorial(n - 1);
}

# ------------------------------------------------------------------------------------------------

# Recursive tree

- Number of branches in a recursive tree represent number of choices
- when generating a recursive tree to form all subsequences of a string "abc"

- the number of branches for each char is 2 - as it has 2 choices 
- either the char will be included in the output or it won't be

# after taking the decision for one element we move on to the next element and take the same decision

- when making a decision we also keep updating our result accordingly

- Suppose - for generating permuation of abc 	--> result = "" if a is not selected 
												--> result = "a" if a is selected

- We will next move on to b and make the same decision for each of these values and keep building result 

# For subsequences, at each character you have two choices:

- Include the character.
- Exclude the character.

For the string "abc", the recursion tree looks like this:

                              ""
                         (index = 0)
                         /          \
                    include a     exclude a
                      "a"             ""
                     /   \           /   \
              include b exclude b include b exclude b
                 "ab"      "a"       "b"       ""
                /   \     /   \     /   \     /   \
            +c     -c  +c    -c  +c    -c  +c    -c
           "abc" "ab" "ac" "a" "bc" "b" "c" ""


# Leaf nodes (all subsequences)

Reading the leaves from left to right:

abc
ab
ac
a
bc
b
c
""

There are 2³ = 8 subsequences for a string of length 3.



