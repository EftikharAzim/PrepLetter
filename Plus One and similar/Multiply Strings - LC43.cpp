/*
Multiply Strings - LeetCode 43

Problem Description:
Given two non-negative integers num1 and num2 represented as strings, return the product 
of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integers directly.

Examples:
Example 1:
Input: num1 = "2", num2 = "3"
Output: "6"

Example 2:
Input: num1 = "123", num2 = "456"
Output: "56088"
Explanation: 123 × 456 = 56088

Example 3:
Input: num1 = "0", num2 = "0"
Output: "0"

Constraints:
• 1 <= num1.length, num2.length <= 200
• num1 and num2 consist of digits only.
• Both num1 and num2 do not contain any leading zero, except the number 0 itself.

Approach: Simulate Manual Multiplication
- Use the grade-school multiplication algorithm
- For numbers of length n and m, result can have at most n+m digits
- Each digit multiplication contributes to specific positions in result
- Handle carry propagation after all multiplications

Key Insight: Position Mapping
- When multiplying digit at position i in num1 with digit at position j in num2
- The result contributes to positions (i+j) and (i+j+1) in the final answer
- Position (i+j) gets the carry, position (i+j+1) gets the remainder

Time Complexity: O(n × m) where n and m are lengths of input strings
Space Complexity: O(n + m) for the result array
*/

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size();
        int m = num2.size();
        
        // Edge case: if either number is "0"
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        
        // Result can have at most n+m digits
        vector<int> result(n + m, 0);
        
        // Multiply each digit of num1 with each digit of num2
        for (int i = n - 1; i >= 0; --i) {           // Process num1 from right to left
            for (int j = m - 1; j >= 0; --j) {       // Process num2 from right to left
                // Multiply current digits
                int mul = (num1[i] - '0') * (num2[j] - '0');
                
                // Add to existing value at position (i+j+1) - this handles overlapping products
                int sum = result[i + j + 1] + mul;
                
                // Store the ones digit at current position
                result[i + j + 1] = sum % 10;
                
                // Add carry to the next higher position
                result[i + j] += sum / 10;
            }
        }
        
        // Convert result array to string, skipping leading zeros
        string res = "";
        bool leadingZero = true;
        
        for (int i = 0; i < n + m; ++i) {
            if (leadingZero && result[i] == 0) {
                continue;  // Skip leading zeros
            }
            leadingZero = false;  // Found first non-zero digit
            res += (result[i] + '0');  // Convert digit to character
        }
        
        // Handle the case where result is "0" (shouldn't happen due to edge case check above)
        return res.empty() ? "0" : res;
    }
    
    /*
    Position mapping example for "123" × "45":
    
    Positions in result array:  0  1  2  3  4
    
    When i=2, j=1: multiply 3×4
    - mul = 12
    - goes to positions (2+1+1)=4 and (2+1)=3
    - result[4] += 12%10 = 2, result[3] += 12/10 = 1
    
    When i=2, j=0: multiply 3×5  
    - mul = 15
    - goes to positions (2+0+1)=3 and (2+0)=2
    - result[3] += 15%10 = 5, result[2] += 15/10 = 1
    
    And so on for all digit pairs...
    
    Visual representation:
        1 2 3
      ×   4 5
      -------
        6 1 5  (123 × 5)
    + 4 9 2 0  (123 × 4, shifted)
    ---------
      5 5 3 5
    */
};