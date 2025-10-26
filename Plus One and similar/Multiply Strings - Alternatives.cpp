/*
Multiply Strings - Alternative Implementations
LeetCode 43

This file demonstrates different approaches to solve the string multiplication problem,
including various optimization strategies and implementation styles.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <reverse>
using namespace std;

// Approach 1: Original Optimized Solution (Most Efficient)
class SolutionOptimal {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        int n = num1.size(), m = num2.size();
        vector<int> result(n + m, 0);
        
        // Grade school multiplication
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = result[i + j + 1] + mul;
                
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }
        
        // Convert to string, skip leading zeros
        string res;
        for (int i = 0; i < n + m; ++i) {
            if (!(res.empty() && result[i] == 0)) {
                res += result[i] + '0';
            }
        }
        
        return res.empty() ? "0" : res;
    }
};

// Approach 2: Reverse Strings for Easier Processing
class SolutionReverse {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        // Reverse for easier index calculation
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        vector<int> result(num1.size() + num2.size(), 0);
        
        // Now we can use direct indexing
        for (int i = 0; i < num1.size(); ++i) {
            for (int j = 0; j < num2.size(); ++j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                result[i + j] += mul;
                
                // Handle carry immediately
                if (result[i + j] >= 10) {
                    result[i + j + 1] += result[i + j] / 10;
                    result[i + j] %= 10;
                }
            }
        }
        
        // Remove trailing zeros and convert to string
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        
        string res;
        for (int i = result.size() - 1; i >= 0; --i) {
            res += result[i] + '0';
        }
        
        return res;
    }
};

// Approach 3: Separate Multiplication and Carry Propagation
class SolutionSeparatePhases {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        int n = num1.size(), m = num2.size();
        vector<int> result(n + m, 0);
        
        // Phase 1: Perform all multiplications without handling carries
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                result[i + j + 1] += mul;
            }
        }
        
        // Phase 2: Handle all carries from right to left
        for (int i = n + m - 1; i > 0; --i) {
            if (result[i] >= 10) {
                result[i - 1] += result[i] / 10;
                result[i] %= 10;
            }
        }
        
        // Phase 3: Convert to string
        string res;
        for (int i = 0; i < n + m; ++i) {
            if (!(res.empty() && result[i] == 0)) {
                res += result[i] + '0';
            }
        }
        
        return res.empty() ? "0" : res;
    }
};

// Approach 4: Karatsuba Algorithm (For Very Large Numbers)
class SolutionKaratsuba {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        return karatsubaMultiply(num1, num2);
    }
    
private:
    string karatsubaMultiply(string x, string y) {
        // Remove leading zeros first
        x = removeLeadingZeros(x);
        y = removeLeadingZeros(y);
        
        // Base case: single digit multiplication
        if (x.length() <= 1 && y.length() <= 1) {
            int digit1 = x.empty() ? 0 : x[0] - '0';
            int digit2 = y.empty() ? 0 : y[0] - '0';
            int result = digit1 * digit2;
            return to_string(result);
        }
        
        // Pad strings to equal length
        int maxLen = max(x.length(), y.length());
        x = string(maxLen - x.length(), '0') + x;
        y = string(maxLen - y.length(), '0') + y;
        
        // If length is odd, pad one more zero
        if (maxLen % 2 == 1) {
            x = "0" + x;
            y = "0" + y;
            maxLen++;
        }
        
        int mid = maxLen / 2;
        
        // Split numbers: x = x1 * 10^mid + x0, y = y1 * 10^mid + y0
        string x1 = x.substr(0, mid);
        string x0 = x.substr(mid);
        string y1 = y.substr(0, mid);
        string y0 = y.substr(mid);
        
        // Recursive calls - the heart of Karatsuba!
        string z2 = karatsubaMultiply(x1, y1);                    // High × High
        string z0 = karatsubaMultiply(x0, y0);                    // Low × Low
        string z1 = karatsubaMultiply(addStrings(x1, x0), 
                                     addStrings(y1, y0));         // (High+Low) × (High+Low)
        
        // z1 = z1 - z2 - z0 (this is the Karatsuba magic!)
        string z2_plus_z0 = addStrings(z2, z0);
        z1 = subtractStrings(z1, z2_plus_z0);
        
        // Result = z2 * 10^(2*mid) + z1 * 10^mid + z0
        string term1 = multiplyByPowerOf10(z2, 2 * mid);  // High order term
        string term2 = multiplyByPowerOf10(z1, mid);      // Middle term  
        string term3 = z0;                                // Low order term
        
        return addStrings(addStrings(term1, term2), term3);
    }
    
    // Helper functions for Karatsuba (simplified implementations)
    string addStrings(string num1, string num2) {
        // Implementation of string addition (similar to Add Binary problem)
        string result = "";
        int carry = 0;
        int i = num1.length() - 1, j = num2.length() - 1;
        
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += num1[i--] - '0';
            if (j >= 0) sum += num2[j--] - '0';
            
            result = char(sum % 10 + '0') + result;
            carry = sum / 10;
        }
        
        return result;
    }
    
    string subtractStrings(string num1, string num2) {
        // Full implementation of string subtraction (assumes num1 >= num2)
        
        // Handle equal numbers
        if (num1 == num2) return "0";
        
        // Pad num2 with leading zeros to match num1 length
        while (num2.length() < num1.length()) {
            num2 = "0" + num2;
        }
        
        string result = "";
        int borrow = 0;
        
        // Subtract digit by digit from right to left
        for (int i = num1.length() - 1; i >= 0; i--) {
            int digit1 = num1[i] - '0' - borrow;
            int digit2 = num2[i] - '0';
            
            if (digit1 < digit2) {
                digit1 += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            
            result = char(digit1 - digit2 + '0') + result;
        }
        
        // Remove leading zeros
        int i = 0;
        while (i < result.length() && result[i] == '0') {
            i++;
        }
        
        return i == result.length() ? "0" : result.substr(i);
    }
    
    string multiplyByPowerOf10(string num, int power) {
        if (num == "0" || power == 0) return num;
        return num + string(power, '0');
    }
    
    // Helper function to remove leading zeros
    string removeLeadingZeros(string num) {
        int i = 0;
        while (i < num.length() && num[i] == '0') {
            i++;
        }
        return i == num.length() ? "0" : num.substr(i);
    }
};

// Approach 5: Using Addition (Repeated Addition - Not Efficient)
class SolutionRepeatedAddition {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        // Choose smaller number for repetition
        if (num2.length() < num1.length()) swap(num1, num2);
        
        string result = "0";
        
        // Add num2 to itself num1 times
        for (char digit : num1) {
            int count = digit - '0';
            string temp = result;
            
            // Multiply current result by 10
            result = result + "0";
            
            // Add num2 'count' times
            for (int i = 0; i < count; ++i) {
                result = addStrings(result, num2);
            }
        }
        
        return result;
    }
    
private:
    string addStrings(string num1, string num2) {
        string result = "";
        int carry = 0;
        int i = num1.length() - 1, j = num2.length() - 1;
        
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += num1[i--] - '0';
            if (j >= 0) sum += num2[j--] - '0';
            
            result = char(sum % 10 + '0') + result;
            carry = sum / 10;
        }
        
        return result;
    }
};

/*
Performance Comparison:

1. Optimal Solution (Grade School):
   - Time: O(n × m)
   - Space: O(n + m)
   - Pros: Simple, efficient for most cases, easy to understand
   - Cons: Not optimal for extremely large numbers

2. Reverse Strings:
   - Time: O(n × m)
   - Space: O(n + m)
   - Pros: Cleaner indexing, easier to handle carries
   - Cons: Extra reverse operations

3. Separate Phases:
   - Time: O(n × m)
   - Space: O(n + m)
   - Pros: Clear separation of concerns, easier to debug
   - Cons: Multiple passes through result array

4. Karatsuba Algorithm:
   - Time: O(n^1.585) for large inputs
   - Space: O(log n) due to recursion
   - Pros: Asymptotically faster for very large numbers
   - Cons: Complex implementation, overhead for small numbers

5. Repeated Addition:
   - Time: O(n × value_of_smaller_number)
   - Space: O(max(n, m))
   - Pros: Uses only addition (conceptually simple)
   - Cons: Extremely inefficient, not practical

Recommendation: Use Optimal Solution for interviews and most practical applications!

Key Insights:
• Position mapping is crucial: digit i × digit j contributes to positions i+j and i+j+1
• Maximum result length is sum of input lengths
• Handle carries properly to avoid overflow
• Leading zero elimination is important for correct output

Common Optimizations:
• Early termination for "0" inputs
• Choose processing order to minimize carries
• Use bit operations where possible (for integer implementations)
• Consider FFT for extremely large number multiplication
*/