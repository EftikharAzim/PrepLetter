/*
Add Binary - LeetCode 67

Problem Description:
Given two binary strings a and b, return their sum as a binary string.

Examples:
Example 1:
Input: a = "11", b = "1"
Output: "100"
Explanation: 11 + 1 = 100 in binary (3 + 1 = 4 in decimal)

Example 2:
Input: a = "1010", b = "1011"
Output: "10101"
Explanation: 1010 + 1011 = 10101 in binary (10 + 11 = 21 in decimal)

Example 3:
Input: a = "0", b = "0"
Output: "0"

Constraints:
• 1 <= a.length, b.length <= 10^4
• a and b consist only of '0' or '1' characters.
• Each string does not contain leading zeros except for the zero itself.

Approach: Simulate Binary Addition
- Process both strings from right to left (least to most significant bit)
- Maintain a carry for overflow (when sum >= 2)
- Handle different string lengths gracefully
- Add remaining carry at the end if needed

Binary Addition Rules:
• 0 + 0 = 0 (no carry)
• 0 + 1 = 1 (no carry)  
• 1 + 0 = 1 (no carry)
• 1 + 1 = 10 in binary (0 with carry 1)
• 1 + 1 + 1 (with carry) = 11 in binary (1 with carry 1)

Time Complexity: O(max(n, m)) where n and m are lengths of a and b
Space Complexity: O(max(n, m)) for the result string
*/

#include <string>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1;  // Pointer for string a (rightmost bit)
        int j = b.size() - 1;  // Pointer for string b (rightmost bit)
        int carry = 0;         // Carry from previous addition
        string result = "";    // Result string (built right to left)
        
        // Process both strings from right to left
        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;   // Start with carry from previous iteration
            
            // Add bit from string a if available
            if (i >= 0) {
                sum += (a[i] - '0');  // Convert char to int
                i--;                  // Move to next bit (leftward)
            }
            
            // Add bit from string b if available
            if (j >= 0) {
                sum += (b[j] - '0');  // Convert char to int
                j--;                  // Move to next bit (leftward)
            }
            
            // Calculate result bit and new carry
            char resultBit = (sum % 2) + '0';  // Current bit: 0 or 1
            result = resultBit + result;       // Prepend to result (building right to left)
            carry = sum / 2;                   // New carry: 0 or 1
        }
        
        return result;
    }
    
    /*
    Step-by-step example: a = "1010", b = "1011"
    
    Initial: i=3, j=3, carry=0, result=""
    
    Iteration 1: (rightmost bits)
    - a[3]='0', b[3]='1' → sum = 0 + 0 + 1 = 1
    - resultBit = 1, carry = 0 → result = "1"
    
    Iteration 2:
    - a[2]='1', b[2]='1' → sum = 0 + 1 + 1 = 2  
    - resultBit = 0, carry = 1 → result = "01"
    
    Iteration 3:
    - a[1]='0', b[1]='0' → sum = 1 + 0 + 0 = 1
    - resultBit = 1, carry = 0 → result = "101"
    
    Iteration 4: (leftmost bits)
    - a[0]='1', b[0]='1' → sum = 0 + 1 + 1 = 2
    - resultBit = 0, carry = 1 → result = "0101"
    
    Iteration 5: (carry remaining)
    - No more bits, but carry = 1 → sum = 1
    - resultBit = 1, carry = 0 → result = "10101"
    
    Final result: "10101"
    */
};