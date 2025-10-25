/*
Backspace String Compare - LeetCode 844

Problem Description:
Given two strings s and t, return true if they are equal when both are typed into empty text editors. 
'#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

Examples:
Example 1:
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".

Example 2:
Input: s = "ab##", t = "#a#c"
Output: true
Explanation: Both s and t become "".

Example 3:
Input: s = "a##c", t = "#a#c"
Output: true
Explanation: Both s and t become "c".

Example 4:
Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".

Constraints:
• 1 <= s.length, t.length <= 200
• s and t only contain lowercase letters and '#' characters.

Approach: Stack Simulation
- Use two stacks to simulate the typing process
- For each character:
  - If it's '#' and stack is not empty: pop (backspace)
  - If it's not '#': push to stack
- Compare final stacks for equality

Time Complexity: O(n + m) where n and m are lengths of s and t
Space Complexity: O(n + m) for the stacks
*/

#include <stack>
using namespace std;

class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char> stk1, stk2;
        
        // Process string s: simulate typing with backspaces
        for(int i = 0; i < (int)s.size(); ++i) {
            if(s[i] == '#' && !stk1.empty()) {
                stk1.pop();  // Backspace: remove last character
            }
            else if(s[i] != '#') {
                stk1.push(s[i]);  // Regular character: add to result
            }
            // Note: If s[i] == '#' and stack is empty, do nothing (can't backspace empty text)
        }

        // Process string t: simulate typing with backspaces
        for(int i = 0; i < (int)t.size(); ++i) {
            if(t[i] == '#' && !stk2.empty()) {
                stk2.pop();  // Backspace: remove last character
            }
            else if(t[i] != '#') {
                stk2.push(t[i]);  // Regular character: add to result
            }
            // Note: If t[i] == '#' and stack is empty, do nothing (can't backspace empty text)
        }
        
        // Compare final results: stacks have built-in equality operator
        return stk1 == stk2;
    }
    
    /*
    Alternative approaches to consider:
    
    1. String Building Approach (O(n+m) time, O(n+m) space):
       - Build final strings instead of using stacks
       - Compare strings directly
    
    2. Two Pointer Approach (O(n+m) time, O(1) space):
       - Process strings from right to left
       - Skip characters that would be backspaced
       - Compare character by character without extra space
       
    3. Recursive Approach:
       - Recursively process each string
       - Handle backspaces during recursion
    */
};