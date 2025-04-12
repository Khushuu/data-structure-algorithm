// 271. Encode and Decode strings (premium)
// Design an algorithm to encode a list of strings into a single string, and a corresponding algorithm to decode that single string back into the original list of strings.

// Input: ["hello", "world"]
// Encoded: "5#hello5#world"
// Decoded: ["hello", "world"]

// Each string is prefixed with its length followed by a delimiter (#). The decoder reads the length first, then extracts the corresponding substring.

// Approach
// We use a length-prefix encoding technique:
// For encoding, prefix each string with its length and a delimiter (#).
// For decoding, read the length first, then extract the string.

// Encoding Steps
// Append the length of each string.
// Add a special delimiter (#).
// Append the actual string.

// Example:

// ["abc", "de"]
// → "3#abc2#de"

// Decoding Steps
// Read the length (before #).
// Extract the string of that length.
// Repeat until all strings are decoded.

// Time and Space Complexity

// Encoding
// Time Complexity: O(N), where N is the total length of all strings.
// Space Complexity: O(1) (excluding output string).

// Decoding
// Time Complexity: O(N), since we traverse the entire encoded string.
// Space Complexity: O(N), since we store the decoded strings in a vector.

// ---------------------------------------------------------------------------------------------------------------

class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {

        string encoded = "";
        for (string s : strs) {
            encoded += to_string(s.size()) + "#" + s; // Prefix with length
        }
        return encoded;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {

        vector<string> decoded;
        int i = 0;

        while (i < s.size()) {
            int j = i;
            while (s[j] != '#') j++; // Find the delimiter '#'
            int length = stoi(s.substr(i, j - i)); // Extract length
            string word = s.substr(j + 1, length); // Extract word
            decoded.push_back(word);
            i = j + 1 + length; // Move to the next encoded string
        }

        return decoded;
    }
};

// ---------------------------------------------------------------------------------------------------------------
