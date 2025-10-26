/*
Longest Substring Without Repeating Characters - LeetCode 3

Problem Description:
Given a string s, find the length of the longest substring without repeating characters.

Examples:
Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

Example 4:
Input: s = ""
Output: 0

Constraints:
• 0 <= s.length <= 5 * 10^4
• s consists of English letters, digits, symbols and spaces.

Approach: Sliding Window with HashMap
- Use two pointers (i, j) to maintain a sliding window
- HashMap stores the most recent index of each character
- When duplicate found: move left pointer to avoid repetition
- Track maximum window size seen so far

Key Insight: When we find a duplicate character, we don't need to move the left pointer
one by one. We can directly jump to the position after the previous occurrence.

Time Complexity: O(n) where n is the length of string s
Space Complexity: O(min(m, n)) where m is the character set size
*/

#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charIndex;  // Maps character to its most recent index
        int left = 0;      // Left pointer of sliding window
        int right = 0;     // Right pointer of sliding window  
        int n = s.size();
        int maxLength = 0; // Maximum length found so far
        
        // Expand the sliding window by moving right pointer
        while (right < n) {
            char currentChar = s[right];
            
            // If character is seen before AND it's within current window
            if (charIndex.count(currentChar) && charIndex[currentChar] >= left) {
                // Move left pointer to position after the duplicate
                left = charIndex[currentChar] + 1;
            }
            
            // Update the most recent index of current character
            charIndex[currentChar] = right;
            
            // Update maximum length if current window is larger
            maxLength = max(maxLength, right - left + 1);
            
            // Move right pointer to expand window
            right++;
        }
        
        return maxLength;
    }
    
    /*
    Step-by-step walkthrough for s = "abcabcbb":
    
    Window: [left, right], Current substring, Action
    
    right=0, char='a': window=[0,0], "a", maxLen=1
    right=1, char='b': window=[0,1], "ab", maxLen=2  
    right=2, char='c': window=[0,2], "abc", maxLen=3
    right=3, char='a': 'a' seen at index 0, window=[1,3], "bca", maxLen=3
    right=4, char='b': 'b' seen at index 1, window=[2,4], "cab", maxLen=3
    right=5, char='c': 'c' seen at index 2, window=[3,5], "abc", maxLen=3
    right=6, char='b': 'b' seen at index 4, window=[5,6], "cb", maxLen=3
    right=7, char='b': 'b' seen at index 6, window=[7,7], "b", maxLen=3
    
    Final answer: 3
    */
};