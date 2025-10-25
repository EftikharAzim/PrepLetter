/*
Remove All Adjacent Duplicates In String - Alternative Approaches
LeetCode 1047

This file demonstrates different ways to solve the duplicate removal problem,
including stack-based and iterative approaches with detailed explanations.
*/

#include <string>
#include <stack>
#include <vector>
using namespace std;

// Approach 1: Explicit Stack (More Traditional)
class SolutionStack {
public:
    string removeDuplicates(string s) {
        stack<char> stk;
        
        // Process each character
        for (char c : s) {
            if (!stk.empty() && stk.top() == c) {
                stk.pop();  // Remove duplicate
            } else {
                stk.push(c);  // Add new character
            }
        }
        
        // Build result string from stack (need to reverse)
        string result = "";
        while (!stk.empty()) {
            result = stk.top() + result;  // Prepend to reverse order
            stk.pop();
        }
        
        return result;
    }
};

// Approach 2: String as Stack (Most Efficient - Original)
class SolutionStringStack {
public:
    string removeDuplicates(string s) {
        string result;
        
        for (char c : s) {
            if (!result.empty() && result.back() == c) {
                result.pop_back();  // Remove duplicate
            } else {
                result.push_back(c);  // Add character
            }
        }
        
        return result;
    }
};

// Approach 3: Two-Pointer In-Place Modification (Space Optimized)
class SolutionTwoPointer {
public:
    string removeDuplicates(string s) {
        int writeIndex = 0;  // Where to write next valid character
        
        for (int readIndex = 0; readIndex < s.length(); readIndex++) {
            // If we have a character at writeIndex-1 and it matches current
            if (writeIndex > 0 && s[writeIndex - 1] == s[readIndex]) {
                writeIndex--;  // "Remove" the previous character
            } else {
                s[writeIndex] = s[readIndex];  // Keep current character
                writeIndex++;
            }
        }
        
        return s.substr(0, writeIndex);  // Return only valid part
    }
};

// Approach 4: Recursive Solution (Educational)
class SolutionRecursive {
public:
    string removeDuplicates(string s) {
        return removeHelper(s);
    }
    
private:
    string removeHelper(const string& s) {
        // Base case: empty or single character
        if (s.length() <= 1) {
            return s;
        }
        
        // Look for first adjacent duplicate pair
        for (int i = 0; i < s.length() - 1; i++) {
            if (s[i] == s[i + 1]) {
                // Remove the duplicate pair and recurse
                string remaining = s.substr(0, i) + s.substr(i + 2);
                return removeHelper(remaining);
            }
        }
        
        // No duplicates found
        return s;
    }
};

/*
Performance Comparison:

1. Explicit Stack Approach:
   - Time: O(n)
   - Space: O(n) for stack + O(n) for result building
   - Pros: Clear stack operations, easy to understand
   - Cons: Extra space and time for result construction

2. String as Stack (Original):
   - Time: O(n) 
   - Space: O(n) for result string only
   - Pros: Most efficient, clean code
   - Cons: None really, this is optimal

3. Two-Pointer In-Place:
   - Time: O(n)
   - Space: O(1) extra space (modifies input)
   - Pros: Space efficient, no extra data structures
   - Cons: Modifies input string, slightly more complex

4. Recursive Approach:
   - Time: O(n²) in worst case due to string operations
   - Space: O(n²) due to recursion and string creation
   - Pros: Functional style, conceptually simple
   - Cons: Very inefficient, can cause stack overflow

Recommendation: Use String as Stack (Approach 2) - it's optimal and clean!

Example walkthrough for "abbaca":
Stack states: [] → [a] → [a,b] → [a] → [] → [c] → [c,a]
Result: "ca"

Key insight: This problem is essentially parentheses matching but with
identical adjacent characters instead of opening/closing brackets!
*/