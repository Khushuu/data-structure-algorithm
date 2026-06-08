## Identification

- subarray + 
    given some size of window + 
        maximum or minimum in window

---------------------------------------------------------------------------------------------------------------------------
## Two types:

- fixed size    ==> window size fixed --> find max or min in window
- dynamic size  ==> given some condition --> find max or min size of window that satisfies the condition 

-------------------------------------------------------------------------------------------------------------------------
# Approach

- have two pointers l and r
- window size = r - l + 1

- for fixed size window when size is k -> compute -> increment l
- always keep moving r

# do something (sum) --> if size becomes k (compute result) & move left pointer --> keep expanding 

# expand right -> window valid (compute result) -> invalid -> shrink window

-------------------------------------------------------------------------------------------------------------------------

# fixed size window format

while(r < n) {

    do some calculation

    if(r - l + 1 == k) {

        deduce result
        shrink window from left -> remove from the running variable
        l++;
    }

    r++;
}

# variable size window format

while(r < n) {

    do some calculations

    make the window valid using while loop and given condition 
        shrink window from left - l++

    if condition is matched 
        deduce result 

    r++ // expand window
}

-------------------------------------------------------------------------------------------------------------------------


## Questions:

# Fixed size window:

- maximum / minimum sum subarray of size k
- first negative number in every window of size k
- **count occurences of anagrams** - **Important** 
- **maximum of all subarrays of size k** - **Important**

# Variable size window

- largest subarray of size k
- longest substring with k unique characters 
- longest substring without repeating characters 
- pick toys
- **minimum window substring** - **Important**   

---------------------------------------------------------------------------------------------------------------------------


