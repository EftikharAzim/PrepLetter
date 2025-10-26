/*
Plus One - LeetCode 66

Problem Description:
You are given a large integer represented as an integer array digits, where each digits[i] is 
the ith digit of the integer. The digits are ordered from most significant to least significant 
in left-to-right order. The large integer does not contain any leading zeros.

Increment the large integer by one and return the resulting array of digits.

Examples:
Example 1:
Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123. Incrementing by one gives 123 + 1 = 124.
Thus, the result should be [1,2,4].

Example 2:
Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321. Incrementing by one gives 4321 + 1 = 4322.
Thus, the result should be [4,3,2,2].

Example 3:
Input: digits = [9]
Output: [1,0]
Explanation: The array represents the integer 9. Incrementing by one gives 9 + 1 = 10.
Thus, the result should be [1,0].

Example 4:
Input: digits = [9,9,9]
Output: [1,0,0,0]
Explanation: The array represents the integer 999. Incrementing by one gives 999 + 1 = 1000.
Thus, the result should be [1,0,0,0].

Constraints:
• 1 <= digits.length <= 100
• 0 <= digits[i] <= 9
• digits does not contain any leading zeros except for the number 0 itself.

Approach: Simulate Manual Addition
- Process digits from right to left (least to most significant)
- Handle carry propagation like manual arithmetic
- Two cases:
  1. Normal case: digit < 9, just increment and return
  2. Carry case: digit = 9, set to 0 and continue (carry over)
- Special case: all digits were 9, need to add new leading 1

Time Complexity: O(n) where n is number of digits
Space Complexity: O(1) extra space (modifies input), O(n) if we count output
*/

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        // Iterate from the least significant digit (rightmost) to most significant (leftmost)
        for (int i = digits.size() - 1; i >= 0; --i) {
            // Case 1: Current digit is less than 9
            if (digits[i] < 9) {
                digits[i] += 1;  // Simply increment and we're done
                return digits;   // No carry needed, return immediately
            }
            
            // Case 2: Current digit is 9 - causes carry
            digits[i] = 0;  // Set current digit to 0 and continue to next iteration
            // The carry will be handled in the next iteration of the loop
        }
        
        // Special Case: All digits were 9 (e.g., [9], [9,9], [9,9,9])
        // The loop completed without returning, meaning we have a carry out
        // Need to add a new leading digit 1 (e.g., 999 + 1 = 1000)
        digits.insert(digits.begin(), 1);
        return digits;
    }
    
    /*
    Step-by-step walkthrough for digits = [1,2,9]:
    
    i=2: digits[2] = 9
         9 + 1 = 10, so digits[2] = 0, continue with carry
         digits = [1,2,0]
    
    i=1: digits[1] = 2  
         2 + 1 = 3 < 10, so digits[1] = 3, return
         digits = [1,3,0]
    
    Result: [1,3,0] (represents 130)
    
    Walkthrough for digits = [9,9,9]:
    
    i=2: digits[2] = 9 → set to 0, carry → digits = [9,9,0]
    i=1: digits[1] = 9 → set to 0, carry → digits = [9,0,0]  
    i=0: digits[0] = 9 → set to 0, carry → digits = [0,0,0]
    Loop ends without return → insert 1 at beginning
    Result: [1,0,0,0] (represents 1000)
    */
};