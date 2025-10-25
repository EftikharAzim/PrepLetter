/*
Backspace String Compare - Alternative Implementations
LeetCode 844

This file contains different approaches to solve the backspace string compare problem.
Each approach has different time/space trade-offs.
*/

#include <string>
#include <vector>
using namespace std;

// Approach 1: String Building (O(n+m) time, O(n+m) space)
class SolutionStringBuilding {
public:
    bool backspaceCompare(string s, string t) {
        return buildFinalString(s) == buildFinalString(t);
    }
    
private:
    string buildFinalString(const string& str) {
        string result;
        for (char c : str) {
            if (c == '#') {
                if (!result.empty()) {
                    result.pop_back();  // Remove last character (backspace)
                }
            } else {
                result.push_back(c);  // Add character
            }
        }
        return result;
    }
};

// Approach 2: Two Pointer Approach (O(n+m) time, O(1) space) - Most Efficient!
/*
KEY INSIGHT: Instead of building the final strings, we can work backwards!
When we process from RIGHT to LEFT:
- We can count backspaces (#) as we go
- When we see a regular character, we check if it gets "cancelled" by backspaces
- This way we find the "final" characters without building intermediate strings

Example walkthrough: s = "ab#c", t = "ad#c"
s: a b # c    (indices: 0 1 2 3)
   ← ← ← ←    (processing direction)
   
Step 1: Start from right (index 3): 'c' - no backspaces yet, so 'c' is valid
Step 2: Move left (index 2): '#' - this is a backspace, count = 1  
Step 3: Move left (index 1): 'b' - but backspace count = 1, so 'b' gets cancelled
Step 4: Move left (index 0): 'a' - backspace count = 0, so 'a' is valid

Final valid characters in s (right to left): 'c', 'a' → "ac" when read left to right
*/

class SolutionTwoPointer {
public:
    bool backspaceCompare(string s, string t) {
        int i = s.length() - 1;  // Pointer for string s (start from end)
        int j = t.length() - 1;  // Pointer for string t (start from end)
        
        // Keep comparing until both strings are fully processed
        while (i >= 0 || j >= 0) {
            // Find next valid (non-backspaced) character in string s
            i = getNextValidChar(s, i);
            // Find next valid (non-backspaced) character in string t  
            j = getNextValidChar(t, j);
            
            // Case 1: Both strings have valid characters to compare
            if (i >= 0 && j >= 0) {
                if (s[i] != t[j]) {
                    return false;  // Characters don't match
                }
                // Move to next character (going backwards)
                i--;
                j--;
            } 
            // Case 2: One string finished, the other has more characters
            else if (i >= 0 || j >= 0) {
                return false;  // Strings have different lengths after processing
            }
            // Case 3: Both strings finished (i < 0 && j < 0) - loop will exit
        }
        
        return true;  // All characters matched perfectly
    }
    
private:
    /*
    This function finds the next character that would actually appear in the final string
    It handles backspaces by "cancelling out" characters as we go backwards
    
    Example: str = "ab#c", starting from index 3
    index=3: 'c' → backspaceCount=0, return 3 (found valid char)
    
    Example: str = "ab#c", starting from index 2  
    index=2: '#' → backspaceCount=1
    index=1: 'b' → backspaceCount>0, so decrement to 0 (b gets cancelled)
    index=0: 'a' → backspaceCount=0, return 0 (found valid char)
    */
    int getNextValidChar(const string& str, int index) {
        int backspaceCount = 0;  // How many characters need to be "cancelled"
        
        // Go backwards through the string
        while (index >= 0) {
            if (str[index] == '#') {
                backspaceCount++;  // Found a backspace - need to cancel next char
            } else {
                // Found a regular character
                if (backspaceCount > 0) {
                    backspaceCount--;  // This character gets cancelled by a backspace
                    // Continue searching (don't return this index)
                } else {
                    break;  // Found a character that survives! Return this index
                }
            }
            index--;  // Move backwards
        }
        
        return index;  // Return index of valid character (or -1 if none found)
    }
};

// Approach 3: Recursive Approach (Educational purposes)
class SolutionRecursive {
public:
    bool backspaceCompare(string s, string t) {
        return processString(s) == processString(t);
    }
    
private:
    string processString(const string& str) {
        if (str.empty()) return "";
        
        // Process from left to right recursively
        return processHelper(str, 0, "");
    }
    
    string processHelper(const string& str, int index, string current) {
        if (index >= str.length()) {
            return current;
        }
        
        char ch = str[index];
        if (ch == '#') {
            if (!current.empty()) {
                current.pop_back();  // Backspace
            }
        } else {
            current.push_back(ch);  // Add character
        }
        
        return processHelper(str, index + 1, current);
    }
};

/*
Performance Comparison:

1. Original Stack Approach:
   - Time: O(n + m)
   - Space: O(n + m) 
   - Pros: Clean, intuitive
   - Cons: Extra space for stacks

2. String Building Approach:
   - Time: O(n + m)
   - Space: O(n + m)
   - Pros: Very readable
   - Cons: Extra space for strings

3. Two Pointer Approach:
   - Time: O(n + m) 
   - Space: O(1)
   - Pros: Most space-efficient, optimal solution
   - Cons: More complex logic

4. Recursive Approach:
   - Time: O(n + m)
   - Space: O(n + m) due to recursion stack
   - Pros: Functional programming style
   - Cons: Stack overflow risk for large inputs

Recommendation: Use Two Pointer approach for optimal performance!
*/