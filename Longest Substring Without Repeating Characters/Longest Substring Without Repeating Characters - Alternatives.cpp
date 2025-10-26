/*
Longest Substring Without Repeating Characters - Alternative Approaches
LeetCode 3

This file demonstrates different ways to solve the longest substring problem,
including various sliding window techniques and optimization strategies.
*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Approach 1: Optimized Sliding Window (HashMap) - Original
class SolutionOptimal {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charIndex;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (charIndex.count(s[right]) && charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            charIndex[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

// Approach 2: Sliding Window with HashSet (More Intuitive)
class SolutionHashSet {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window;
        int left = 0, right = 0, maxLen = 0;
        
        while (right < s.length()) {
            // If character not in current window, expand window
            if (window.find(s[right]) == window.end()) {
                window.insert(s[right]);
                maxLen = max(maxLen, right - left + 1);
                right++;
            } else {
                // Shrink window from left until duplicate is removed
                window.erase(s[left]);
                left++;
            }
        }
        
        return maxLen;
    }
};

// Approach 3: Array-based HashMap (For ASCII characters)
class SolutionArray {
public:
    int lengthOfLongestSubstring(string s) {
        // ASCII has 128 characters, extended ASCII has 256
        vector<int> charIndex(128, -1);
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // If character seen before and within current window
            if (charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            charIndex[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

// Approach 4: Brute Force (Check All Substrings) - O(n³)
class SolutionBruteForce {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLen = 0;
        
        // Check every possible substring
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (hasUniqueChars(s, i, j)) {
                    maxLen = max(maxLen, j - i + 1);
                }
            }
        }
        
        return maxLen;
    }
    
private:
    bool hasUniqueChars(const string& s, int start, int end) {
        unordered_set<char> chars;
        for (int i = start; i <= end; i++) {
            if (chars.count(s[i])) {
                return false;
            }
            chars.insert(s[i]);
        }
        return true;
    }
};

// Approach 5: Two-Pass Sliding Window (Educational)
class SolutionTwoPass {
public:
    int lengthOfLongestSubstring(string s) {
        int maxLen = 0;
        
        for (int start = 0; start < s.length(); start++) {
            unordered_set<char> seen;
            
            // Expand from current start position
            for (int end = start; end < s.length(); end++) {
                if (seen.count(s[end])) {
                    break;  // Found duplicate, stop expanding
                }
                seen.insert(s[end]);
                maxLen = max(maxLen, end - start + 1);
            }
        }
        
        return maxLen;
    }
};

// Approach 6: Recursive Solution (Not Efficient)
class SolutionRecursive {
public:
    int lengthOfLongestSubstring(string s) {
        return helper(s, 0, unordered_set<char>());
    }
    
private:
    int helper(const string& s, int index, unordered_set<char> current) {
        if (index >= s.length()) {
            return current.size();
        }
        
        char ch = s[index];
        
        // If character already in set, we can't extend
        if (current.count(ch)) {
            return current.size();
        }
        
        // Try including current character
        current.insert(ch);
        int includeLength = helper(s, index + 1, current);
        current.erase(ch);
        
        // Try starting fresh from next position
        unordered_set<char> fresh;
        int freshLength = helper(s, index + 1, fresh);
        
        return max(includeLength, freshLength);
    }
};

/*
Performance Comparison:

1. Optimized Sliding Window (HashMap):
   - Time: O(n)
   - Space: O(min(m, n)) where m is character set size
   - Pros: Most efficient, single pass, optimal
   - Cons: Slightly complex logic with index checking

2. Sliding Window (HashSet):
   - Time: O(n) 
   - Space: O(min(m, n))
   - Pros: More intuitive, clear shrink/expand logic
   - Cons: May shrink window one character at a time

3. Array-based HashMap:
   - Time: O(n)
   - Space: O(1) for fixed character set
   - Pros: Fastest for ASCII, constant space
   - Cons: Limited to specific character sets

4. Brute Force:
   - Time: O(n³)
   - Space: O(min(m, n))
   - Pros: Simple to understand and implement
   - Cons: Too slow for large inputs

5. Two-Pass Sliding Window:
   - Time: O(n²)
   - Space: O(min(m, n))
   - Pros: Easier to understand than optimal solution
   - Cons: Redundant work, not optimal

6. Recursive Solution:
   - Time: O(2^n) exponential
   - Space: O(n) recursion stack
   - Pros: Functional programming approach
   - Cons: Extremely inefficient, not practical

Recommendation: Use Optimized Sliding Window for interviews!

Key Patterns in This Problem:

1. SLIDING WINDOW TECHNIQUE:
   • Two pointers to maintain a valid window
   • Expand window when conditions are met
   • Contract window when conditions are violated

2. HASHMAP FOR TRACKING:
   • Store character positions or existence
   • Quick O(1) lookup for duplicates
   • Update tracking as window moves

3. OPTIMIZATION INSIGHT:
   • Don't move left pointer one by one
   • Jump directly to position after duplicate
   • This reduces time from O(2n) to O(n)

Common Variations:
• Longest substring with at most K distinct characters
• Longest substring with at most K repeating characters  
• Minimum window substring
• Sliding window maximum/minimum
*/