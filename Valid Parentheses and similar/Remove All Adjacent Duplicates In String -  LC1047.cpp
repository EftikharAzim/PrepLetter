/*
Remove All Adjacent Duplicates In String - LeetCode 1047

Problem Description:
You are given a string s consisting of lowercase English letters. A duplicate removal consists of 
choosing two adjacent and equal characters and removing them.

We repeatedly make duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. 
It can be proven that the answer is unique.

Examples:
Example 1:
Input: s = "abbaca"
Output: "ca"
Explanation: 
For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal,
and this is the only possible move. The result of this move is that the string becomes "aaca",
of which only "aa" is possible, so the final string is "ca".

Example 2:
Input: s = "azxxzy"
Output: "ay"
Explanation: 
Remove "xx" → "azzy"
Remove "zz" → "ay"

Constraints:
• 1 <= s.length <= 10^5
• s consists of lowercase English letters only.

Approach: Stack-like String Building
- Use a result string as a stack
- For each character:
  - If result is not empty AND top character equals current: remove top (duplicate found)
  - Otherwise: add current character to result
- Continue until all characters processed

Time Complexity: O(n) where n is the length of string s
Space Complexity: O(n) for the result string (which also serves as our stack)

Key Insight: This is similar to balanced parentheses, but with duplicate removal instead!
*/

#include <string>
using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        string res;  // Acts as both result and stack
        
        // Process each character in the input string
        for (int i = 0; i < s.size(); ++i) {
            // Check if current character matches the top of our "stack"
            if (!res.empty() && res.back() == s[i]) {
                res.pop_back();  // Remove duplicate pair
            } else {
                res.push_back(s[i]);  // Add character to result
            }
        }
        
        return res;  // Return the final string with all duplicates removed
    }
    
    /*
    Alternative implementation using explicit stack:
    
    string removeDuplicates(string s) {
        stack<char> stk;
        for (char c : s) {
            if (!stk.empty() && stk.top() == c) {
                stk.pop();
            } else {
                stk.push(c);
            }
        }
        
        string result = "";
        while (!stk.empty()) {
            result = stk.top() + result;
            stk.pop();
        }
        return result;
    }
    
    Step-by-step example: s = "abbaca"
    i=0: 'a' → res="" → add 'a' → res="a"
    i=1: 'b' → res="a", 'b' != 'a' → add 'b' → res="ab" 
    i=2: 'b' → res="ab", 'b' == 'b' → remove → res="a"
    i=3: 'a' → res="a", 'a' == 'a' → remove → res=""
    i=4: 'c' → res="" → add 'c' → res="c"
    i=5: 'a' → res="c", 'a' != 'c' → add 'a' → res="ca"
    Final: "ca"
    */
};