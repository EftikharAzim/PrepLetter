/*
Multiply Strings - Detailed Walkthrough and Visual Demonstrations
LeetCode 43

This file contains step-by-step walkthroughs and visual representations
to understand how string multiplication works algorithmically.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class MultiplyStringsDemo {
public:
    string multiplyWithDebug(string num1, string num2) {
        cout << "\n" << string(60, '=') << endl;
        cout << "MULTIPLYING: \"" << num1 << "\" × \"" << num2 << "\"" << endl;
        cout << string(60, '=') << endl;
        
        if (num1 == "0" || num2 == "0") {
            cout << "One of the numbers is 0, result is 0" << endl;
            return "0";
        }
        
        int n = num1.size();
        int m = num2.size();
        vector<int> result(n + m, 0);
        
        cout << "\nStep 1: Initialize result array of size " << (n + m) << endl;
        cout << "Initial result: ";
        printArray(result);
        
        cout << "\nStep 2: Process each digit pair" << endl;
        cout << "Format: num1[i] × num2[j] = product → add to positions (i+j) and (i+j+1)" << endl;
        cout << string(70, '-') << endl;
        
        int stepNum = 1;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int digit1 = num1[i] - '0';
                int digit2 = num2[j] - '0';
                int mul = digit1 * digit2;
                int sum = result[i + j + 1] + mul;
                
                cout << "Step " << setw(2) << stepNum++ << ": ";
                cout << "num1[" << i << "]=" << digit1 << " × num2[" << j << "]=" << digit2;
                cout << " = " << mul;
                cout << " → positions (" << (i+j) << ", " << (i+j+1) << ")" << endl;
                
                cout << "         Before: result[" << (i+j+1) << "]=" << result[i+j+1];
                cout << ", result[" << (i+j) << "]=" << result[i+j] << endl;
                
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
                
                cout << "         After:  result[" << (i+j+1) << "]=" << result[i+j+1];
                cout << ", result[" << (i+j) << "]=" << result[i+j];
                cout << " (sum=" << sum << ", remainder=" << (sum%10) << ", carry=" << (sum/10) << ")" << endl;
                
                cout << "         Array:  ";
                printArray(result);
                cout << endl;
            }
        }
        
        cout << "\nStep 3: Convert to string, removing leading zeros" << endl;
        string res = "";
        bool leadingZero = true;
        
        for (int i = 0; i < n + m; ++i) {
            if (leadingZero && result[i] == 0) {
                cout << "Skipping leading zero at position " << i << endl;
                continue;
            }
            leadingZero = false;
            res += (result[i] + '0');
            cout << "Adding digit " << result[i] << " → current result: \"" << res << "\"" << endl;
        }
        
        if (res.empty()) res = "0";
        
        cout << "\nFinal result: \"" << res << "\"" << endl;
        return res;
    }
    
private:
    void printArray(const vector<int>& arr) {
        cout << "[";
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i];
            if (i < arr.size() - 1) cout << ", ";
        }
        cout << "]";
    }
};

void visualMultiplication(const string& num1, const string& num2) {
    cout << "\n" << string(50, '=') << endl;
    cout << "VISUAL GRADE SCHOOL MULTIPLICATION" << endl;
    cout << string(50, '=') << endl;
    
    cout << "\nTraditional way:" << endl;
    
    // Align numbers for visual multiplication
    int maxLen = max(num1.length(), num2.length());
    string paddedNum1 = string(maxLen - num1.length() + 2, ' ') + num1;
    string paddedNum2 = "× " + string(maxLen - num2.length(), ' ') + num2;
    
    cout << paddedNum1 << endl;
    cout << paddedNum2 << endl;
    cout << string(paddedNum1.length(), '-') << endl;
    
    // Show partial products
    vector<string> partialProducts;
    
    for (int j = num2.length() - 1; j >= 0; --j) {
        int digit2 = num2[j] - '0';
        string partial = "";
        int carry = 0;
        
        // Add trailing zeros for position
        for (int k = 0; k < num2.length() - 1 - j; ++k) {
            partial = "0" + partial;
        }
        
        // Multiply num1 by current digit of num2
        for (int i = num1.length() - 1; i >= 0; --i) {
            int digit1 = num1[i] - '0';
            int product = digit1 * digit2 + carry;
            partial = char(product % 10 + '0') + partial;
            carry = product / 10;
        }
        
        if (carry > 0) {
            partial = char(carry + '0') + partial;
        }
        
        // Pad for alignment
        string paddedPartial = string(paddedNum1.length() - partial.length(), ' ') + partial;
        cout << paddedPartial;
        
        if (j < num2.length() - 1) {
            cout << "  (" << num1 << " × " << digit2 << ")";
        } else {
            cout << "  (" << num1 << " × " << digit2 << ")";
        }
        cout << endl;
        
        partialProducts.push_back(partial);
    }
    
    if (partialProducts.size() > 1) {
        cout << string(paddedNum1.length(), '-') << endl;
        
        // Show final addition (simplified)
        MultiplyStringsDemo demo;
        string result = demo.multiplyWithDebug(num1, num2);
        
        string paddedResult = string(paddedNum1.length() - result.length(), ' ') + result;
        cout << paddedResult << "  (final sum)" << endl;
    }
}

void positionMappingDemo() {
    cout << "\n" << string(50, '=') << endl;
    cout << "POSITION MAPPING EXPLANATION" << endl;
    cout << string(50, '=') << endl;
    
    string num1 = "123";
    string num2 = "45";
    
    cout << "For " << num1 << " × " << num2 << ":" << endl;
    cout << "\nResult array positions:" << endl;
    cout << "Index:  0   1   2   3   4" << endl;
    cout << "Value: [ ] [ ] [ ] [ ] [ ]" << endl;
    
    cout << "\nPosition calculation: i + j + 1 (for ones), i + j (for carry)" << endl;
    cout << "Where i is index in num1, j is index in num2 (both 0-based from left)" << endl;
    
    cout << "\nDetailed mapping:" << endl;
    
    int n = num1.size();
    int m = num2.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char digit1 = num1[i];
            char digit2 = num2[j];
            int onesPos = i + j + 1;
            int carryPos = i + j;
            
            cout << "num1[" << i << "]=" << digit1 << " × num2[" << j << "]=" << digit2;
            cout << " → ones position: " << onesPos << ", carry position: " << carryPos << endl;
        }
    }
    
    cout << "\nWhy this mapping works:" << endl;
    cout << "• In decimal multiplication, digit at position i contributes to 10^i place value" << endl;
    cout << "• When multiplying digits at positions i and j, result affects 10^(i+j) place" << endl;
    cout << "• Array is 0-indexed from left, but positions represent right-to-left significance" << endl;
}

void carryPropagationDemo() {
    cout << "\n" << string(50, '=') << endl;
    cout << "CARRY PROPAGATION ANALYSIS" << endl;
    cout << string(50, '=') << endl;
    
    cout << "Example: 99 × 99 (maximum single-digit carries)" << endl;
    
    vector<int> result(4, 0);  // 99 × 99 needs at most 4 digits
    
    cout << "\nStep-by-step with carries:" << endl;
    
    // 9 × 9 = 81
    cout << "Step 1: 9 × 9 = 81" << endl;
    cout << "        Position 3 gets 81%10 = 1, Position 2 gets 81/10 = 8" << endl;
    result[3] = 1;
    result[2] = 8;
    cout << "        Result: [0, 0, 8, 1]" << endl;
    
    // 9 × 9 = 81 (different position)
    cout << "\nStep 2: 9 × 9 = 81 (tens × ones)" << endl;
    cout << "        Position 2 += 81%10 = 1 → 8+1=9, Position 1 += 81/10 = 8" << endl;
    result[2] += 1;
    result[1] += 8;
    cout << "        Result: [0, 8, 9, 1]" << endl;
    
    // Continue for all positions...
    cout << "\n... (continuing for all digit pairs) ..." << endl;
    cout << "\nFinal insight: Each position can accumulate multiple products" << endl;
    cout << "Maximum value per position before carry: 9×9×min(i+1,j+1) ≈ 81×2 = 162" << endl;
    cout << "So carry can be at most 16, which fits in int" << endl;
}

int main() {
    cout << "MULTIPLY STRINGS - COMPREHENSIVE WALKTHROUGH" << endl;
    
    MultiplyStringsDemo demo;
    
    // Test cases with full debugging
    vector<pair<string, string>> testCases = {
        {"23", "456"},        // Medium complexity
        {"99", "99"},         // Maximum carries
        {"123", "0"},         // Zero case
        {"1", "1"},          // Minimal case
        {"12", "34"},        // Simple case for visual demo
    };
    
    cout << "\nDETAILED ALGORITHM EXECUTION:" << endl;
    
    for (const auto& [num1, num2] : testCases) {
        demo.multiplyWithDebug(num1, num2);
        cout << "\n" << string(40, '=') << endl;
    }
    
    // Visual demonstrations
    visualMultiplication("123", "45");
    positionMappingDemo();
    carryPropagationDemo();
    
    cout << "\n" << string(50, '=') << endl;
    cout << "KEY INSIGHTS AND PATTERNS" << endl;
    cout << string(50, '=') << endl;
    
    cout << "\n1. POSITION MAPPING FORMULA:" << endl;
    cout << "   • For digits at positions i and j:" << endl;
    cout << "   • Ones digit goes to position i+j+1" << endl;
    cout << "   • Carry goes to position i+j" << endl;
    cout << "   • This naturally handles place values!" << endl;
    
    cout << "\n2. RESULT ARRAY SIZE:" << endl;
    cout << "   • Maximum size needed: len(num1) + len(num2)" << endl;
    cout << "   • Example: 999 × 999 = 998001 (3+3=6 digits max, actual=6)" << endl;
    cout << "   • Example: 99 × 99 = 9801 (2+2=4 digits max, actual=4)" << endl;
    
    cout << "\n3. CARRY HANDLING:" << endl;
    cout << "   • Each position can accumulate multiple products" << endl;
    cout << "   • Handle carry: position[i] = sum % 10, position[i-1] += sum / 10" << endl;
    cout << "   • Process carries immediately or in separate phase" << endl;
    
    cout << "\n4. LEADING ZERO ELIMINATION:" << endl;
    cout << "   • Result array may have leading zeros" << endl;
    cout << "   • Skip leading zeros when building final string" << endl;
    cout << "   • Special case: if all zeros, return \"0\"" << endl;
    
    cout << "\n5. OPTIMIZATION INSIGHTS:" << endl;
    cout << "   • Early termination for zero inputs" << endl;
    cout << "   • Process in order that minimizes intermediate values" << endl;
    cout << "   • Consider Karatsuba for very large numbers (O(n^1.585))" << endl;
    
    cout << "\n6. IMPLEMENTATION TIPS:" << endl;
    cout << "   • Use 0-based indexing consistently" << endl;
    cout << "   • Convert char to int: ch - '0'" << endl;
    cout << "   • Convert int to char: digit + '0'" << endl;
    cout << "   • Handle edge cases: \"0\", single digits" << endl;
    
    return 0;
}

/*
DEBUGGING CHECKLIST:
1. Verify position mapping: i+j+1 for ones, i+j for carry
2. Check array bounds: result size should be n+m
3. Handle carries properly: sum%10 and sum/10
4. Remove leading zeros correctly
5. Test edge cases: "0", "1", large numbers

MENTAL MODEL:
Think of it as grade school multiplication:
- Each digit of first number multiplies with each digit of second
- Products are placed at correct positions based on place values  
- Carries are propagated left (toward more significant positions)
- Final result is sum of all positioned products

COMMON PITFALLS:
- Wrong position calculation (forgetting the +1 for ones position)
- Not handling carries properly
- Forgetting to remove leading zeros
- Array size too small (should be n+m, not n*m)
- Not handling "0" input case
*/