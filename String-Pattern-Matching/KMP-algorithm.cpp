// Precompute LPS array - Longest Prefix that is also a Suffix
// How does this help??
// We don't need to jump all the way back in the pattern in the first index
// just skip the strings which is also a prefix and start from that point onwards 
// e.g
// text = "o n i o n i o n s p  l"
//    i =  0 1 2 3 4 5 6 7 8 9 10
// pattern = "o n i o n s"
//       j =  0 1 2 3 4 5

// Actual matching - LPS already computed
// the match happens till i = 4 and j = 4
// i = 5 and j = 5 -- 'i' != 's'
// instead of resetting j to 0
// just check for the string "onion" i.e 1 char before current j value
// what is the length of the longest prefix that is also a suffix 
// so in onion for j = 4 lps array will have lps[4] = 2
// which means that the longest string which is a prefix as well as suffix in onion is of length 2
// "on" is both a suffix and a prefix
// as the front and the end part of the string is same for length 2
// we jump to index 2 by setting j = 2 from where the difference start and compare with i value
// so j = 2 is compared with i = 5 now

// LPS for pattern: "onions"
// LPS: [0,0,0,1,2,0] - for onio -> longest prefix that is also a suffix is o = 1
// for onion --> longest prefix that is also a suffix is on -> 2

//  if (text[i] == pattern[j]) { i++; j++; } when the text and pattern character matches
// else { if (j != 0) j = lps[j - 1]; else i++; } if j is not the first char check the lps table
// if it is the first char just move forward and check first char of pattern with ith char in text 
// if (j == m) { result.push_back(i - j); j = lps[j - 1] }; // if match if found push the start index that matches from text to result and again set j to lps[j - 1]

// KMP code
// T.C = O(m + n) - preprocessing LPS - O(m), pattern matching - O(n) = O(m + n)
// S.C = O(m)- array of size m for storing lps
//---------------------------------------------------------------------------------------------------------------
// Function to compute the LPS array
void computeLPSArray(string pattern, vector<int>& lps) {
    int m = pattern.length();
    int len = 0; // length of the longest substring till i that is a prefix and a suffix
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Matching Function
vector<int> KMPSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps(m, 0);
    computeLPSArray(pattern, lps);

    vector<int> result;
    int i = 0, j = 0; // i for text, j for pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
		else {
			if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
		}

        if (j == m) {
            result.push_back(i - j); // Match found
            j = lps[j - 1];
        } 
    }

    return result;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    vector<int> matches = KMPSearch(text, pattern);

    cout << "Pattern found at indices: ";
    for (int idx : matches) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
//---------------------------------------------------------------------------------------------------------------