/*
Given a string containing just the characters '(', ')', '{', '}', '[', and ']', check if the input string is valid. A string is valid
if:
• Open brackets are closed by the same type of brackets.
• Open brackets are closed in the correct order.

Example 1:
Input: "([)]"
Output: false

Example 2:
Input: "{[]}"
Output: true
*/

#include <unordered_map>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> matched {
            { ')', '(' },
            { '}', '{' },
            { ']', '[' }
        };
        stack<char> stk;
        for(auto &ch : s) {
            // if it's an opening bracket, push to stack
            if(ch == '(' || ch == '{' || ch == '[') {
                stk.push(ch);
            }
            // if it's a closing bracket, check for matching opening bracket
            else if(!stk.empty() && stk.top() == matched[ch]) {
                stk.pop();
            }
            // mismatched closing bracket
            else {
                return false;
            }
        }
        return stk.empty();
    }
};