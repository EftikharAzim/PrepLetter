/*
Longest Substring Without Repeating Characters - Interview Follow-up Questions
LeetCode 3 and Related Problems

This file covers comprehensive follow-up questions that interviewers commonly ask
after solving the basic longest substring problem. These questions test deeper
understanding and problem-solving adaptability.
*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
=================== CATEGORY 1: CONSTRAINT VARIATIONS ===================
*/

// Follow-up 1: What if we can have at most K distinct characters?
// Sliding Window with At Most K Distinct Characters
class SolutionKDistinct {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) return 0;
        
        unordered_map<char, int> charCount;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            charCount[s[right]]++;
            
            // Shrink window if we have more than k distinct characters
            while (charCount.size() > k) {
                charCount[s[left]]--;
                if (charCount[s[left]] == 0) {
                    charCount.erase(s[left]);
                }
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

// Follow-up 2: What if we can have at most K repeating characters?
// Longest Substring with At Most K Repeating Characters
class SolutionKRepeating {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> count;
        int left = 0, maxCount = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s[right]]++;
            maxCount = max(maxCount, count[s[right]]);
            
            // If window size - max frequency > k, shrink window
            if (right - left + 1 - maxCount > k) {
                count[s[left]]--;
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

/*
=================== CATEGORY 2: RETURN VALUE VARIATIONS ===================
*/

// Follow-up 3: Instead of length, return the actual substring
class SolutionReturnString {
public:
    string longestSubstring(string s) {
        unordered_map<char, int> charIndex;
        int left = 0, maxLen = 0, bestStart = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (charIndex.count(s[right]) && charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            charIndex[s[right]] = right;
            
            if (right - left + 1 > maxLen) {
                maxLen = right - left + 1;
                bestStart = left;
            }
        }
        
        return s.substr(bestStart, maxLen);
    }
};

// Follow-up 4: Return all substrings of maximum length
class SolutionAllMaxSubstrings {
public:
    vector<string> allLongestSubstrings(string s) {
        vector<string> result;
        unordered_map<char, int> charIndex;
        int left = 0, maxLen = 0;
        
        // First pass: find maximum length
        for (int right = 0; right < s.length(); right++) {
            if (charIndex.count(s[right]) && charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            charIndex[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        // Second pass: collect all substrings of maximum length
        charIndex.clear();
        left = 0;
        for (int right = 0; right < s.length(); right++) {
            if (charIndex.count(s[right]) && charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            charIndex[s[right]] = right;
            
            if (right - left + 1 == maxLen) {
                result.push_back(s.substr(left, maxLen));
            }
        }
        
        return result;
    }
};

/*
=================== CATEGORY 3: COMPLEXITY OPTIMIZATIONS ===================
*/

// Follow-up 5: What if input is very large? Can we optimize space?
// Space-optimized solution for ASCII characters
class SolutionSpaceOptimized {
public:
    int lengthOfLongestSubstring(string s) {
        // Use array instead of hash map for ASCII characters
        int charIndex[128];
        fill(charIndex, charIndex + 128, -1);
        
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            charIndex[s[right]] = right;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

// Follow-up 6: Can we solve it with O(1) space for specific character sets?
// Bit manipulation for lowercase letters only
class SolutionBitManipulation {
public:
    int lengthOfLongestSubstring(string s) {
        // Only works for lowercase letters a-z
        int left = 0, maxLen = 0;
        int charMask = 0; // Bit mask to track characters
        
        for (int right = 0; right < s.length(); right++) {
            int charBit = 1 << (s[right] - 'a');
            
            // If character already exists in current window
            while (charMask & charBit) {
                charMask &= ~(1 << (s[left] - 'a'));
                left++;
            }
            
            charMask |= charBit;
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

/*
=================== CATEGORY 4: DATA STRUCTURE VARIATIONS ===================
*/

// Follow-up 7: What if we use different data structures?
// Deque-based solution
#include <deque>
class SolutionDeque {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> seen;
        deque<char> window;
        int maxLen = 0;
        
        for (char c : s) {
            while (seen.count(c)) {
                char front = window.front();
                window.pop_front();
                seen.erase(front);
            }
            
            window.push_back(c);
            seen.insert(c);
            maxLen = max(maxLen, (int)window.size());
        }
        
        return maxLen;
    }
};

/*
=================== CATEGORY 5: STREAMING/ONLINE ALGORITHMS ===================
*/

// Follow-up 8: What if the string comes as a stream?
// Online algorithm for streaming input
class StreamingSolution {
private:
    unordered_map<char, int> charIndex;
    string buffer;
    int left;
    int maxLen;
    
public:
    StreamingSolution() : left(0), maxLen(0) {}
    
    void addCharacter(char c) {
        buffer.push_back(c);
        int right = buffer.size() - 1;
        
        if (charIndex.count(c) && charIndex[c] >= left) {
            left = charIndex[c] + 1;
        }
        charIndex[c] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    
    int getCurrentMaxLength() {
        return maxLen;
    }
};

/*
=================== CATEGORY 6: SPECIAL CASES & EDGE HANDLING ===================
*/

// Follow-up 9: Handle Unicode characters
class SolutionUnicode {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<string, int> charIndex;
        int left = 0, maxLen = 0;
        
        for (int right = 0; right < s.length(); ) {
            // Extract UTF-8 character
            string utf8char = extractUTF8Character(s, right);
            
            if (charIndex.count(utf8char) && charIndex[utf8char] >= left) {
                left = charIndex[utf8char] + 1;
            }
            charIndex[utf8char] = right;
            maxLen = max(maxLen, right - left + 1);
            
            right += utf8char.length();
        }
        
        return maxLen;
    }
    
private:
    string extractUTF8Character(const string& s, int pos) {
        // Simplified UTF-8 extraction (1-4 bytes)
        if (pos >= s.length()) return "";
        
        unsigned char c = s[pos];
        if (c < 0x80) return s.substr(pos, 1);        // 1 byte
        else if (c < 0xE0) return s.substr(pos, 2);   // 2 bytes
        else if (c < 0xF0) return s.substr(pos, 3);   // 3 bytes
        else return s.substr(pos, 4);                 // 4 bytes
    }
};

/*
=================== CATEGORY 7: MULTI-DIMENSIONAL EXTENSIONS ===================
*/

// Follow-up 10: 2D version - Largest rectangle with unique characters
#include <stack>
class Solution2D {
public:
    int largestRectangleUniqueChars(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int rows = matrix.size(), cols = matrix[0].size();
        int maxArea = 0;
        
        // For each row as base
        for (int base = 0; base < rows; base++) {
            vector<int> heights(cols, 0);
            
            // Build height array for current base
            for (int r = base; r < rows; r++) {
                unordered_set<char> rowChars;
                bool hasDuplicate = false;
                
                for (int c = 0; c < cols; c++) {
                    if (rowChars.count(matrix[r][c])) {
                        hasDuplicate = true;
                        break;
                    }
                    rowChars.insert(matrix[r][c]);
                    heights[c] = r - base + 1;
                }
                
                if (!hasDuplicate) {
                    maxArea = max(maxArea, largestRectangleInHistogram(heights));
                }
            }
        }
        
        return maxArea;
    }
    
private:
    int largestRectangleInHistogram(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        
        for (int i = 0; i <= heights.size(); i++) {
            int h = (i == heights.size()) ? 0 : heights[i];
            
            while (!st.empty() && h < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        
        return maxArea;
    }
};

/*
=================== COMMON INTERVIEW QUESTIONS SUMMARY ===================

1. CONSTRAINT MODIFICATIONS:
   - "What if we can repeat at most K characters?"
   - "What if we need exactly K distinct characters?"
   - "What if characters have different weights/costs?"

2. OUTPUT VARIATIONS:
   - "Return the actual substring instead of length"
   - "Return all substrings of maximum length"
   - "Return starting positions of all max-length substrings"

3. PERFORMANCE OPTIMIZATION:
   - "Can you optimize for space complexity?"
   - "What if the string is very large (doesn't fit in memory)?"
   - "Can you solve it with O(1) space for specific character sets?"

4. STREAMING/REAL-TIME:
   - "What if characters come one by one in a stream?"
   - "How would you handle dynamic updates (insertions/deletions)?"
   - "What if we need to query the result frequently during construction?"

5. SPECIAL CHARACTER HANDLING:
   - "How would you handle Unicode characters?"
   - "What about case sensitivity?"
   - "How to handle null characters or special symbols?"

6. RELATED PROBLEMS:
   - "Solve the 2D version (matrix)"
   - "What about circular strings?"
   - "How about finding the shortest substring with all unique characters?"

7. ALGORITHM VARIATIONS:
   - "Can you solve it recursively?"
   - "What about using different data structures (trie, segment tree)?"
   - "How would you parallelize this algorithm?"

8. COMPLEXITY ANALYSIS:
   - "Prove the time complexity is O(n)"
   - "What's the space complexity in worst case?"
   - "How does performance change with different character set sizes?"

PREPARATION TIPS:
- Practice sliding window template for variations
- Understand when to use HashMap vs HashSet vs Array
- Know how to modify the algorithm for different constraints
- Be ready to implement streaming/online versions
- Understand the trade-offs between different approaches
*/