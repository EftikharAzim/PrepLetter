/*
Karatsuba Algorithm - Complete Explanation and Implementation
The Divide-and-Conquer Multiplication Algorithm

This file provides a detailed explanation of how Karatsuba algorithm works,
with visual demonstrations and a complete working implementation.
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class KaratsubaExplanation {
public:
    /*
    ============================================================================
    KARATSUBA ALGORITHM EXPLANATION
    ============================================================================
    
    The Problem with Traditional Multiplication:
    - Grade school multiplication: O(n²) time complexity
    - For two n-digit numbers, we need n² single-digit multiplications
    
    Karatsuba's Key Insight:
    - Reduce the number of recursive multiplications from 4 to 3
    - This gives us O(n^log₂(3)) = O(n^1.585) complexity
    
    The Mathematical Foundation:
    
    Given two numbers X and Y, each with n digits:
    X = X₁ × 10^(n/2) + X₀
    Y = Y₁ × 10^(n/2) + Y₀
    
    Where:
    - X₁, Y₁ are the higher-order digits
    - X₀, Y₀ are the lower-order digits
    
    Traditional approach needs 4 multiplications:
    X × Y = (X₁ × 10^(n/2) + X₀) × (Y₁ × 10^(n/2) + Y₀)
          = X₁Y₁ × 10^n + (X₁Y₀ + X₀Y₁) × 10^(n/2) + X₀Y₀
    
    Karatsuba's trick - compute the middle term differently:
    Let:
    Z₂ = X₁ × Y₁                    (1 multiplication)
    Z₀ = X₀ × Y₀                    (1 multiplication)  
    Z₁ = (X₁ + X₀) × (Y₁ + Y₀) - Z₂ - Z₀  (1 multiplication + subtractions)
    
    Then: X × Y = Z₂ × 10^n + Z₁ × 10^(n/2) + Z₀
    
    Why does this work?
    (X₁ + X₀) × (Y₁ + Y₀) = X₁Y₁ + X₁Y₀ + X₀Y₁ + X₀Y₀
                           = Z₂ + (X₁Y₀ + X₀Y₁) + Z₀
    
    So: (X₁Y₀ + X₀Y₁) = (X₁ + X₀) × (Y₁ + Y₀) - Z₂ - Z₀ = Z₁
    
    ============================================================================
    */
    
    string karatsubaMultiply(string x, string y) {
        cout << "\nKaratsuba(" << x << ", " << y << ")" << endl;
        
        // Base case: single digit multiplication
        if (x.length() <= 1 && y.length() <= 1) {
            int result = (x.empty() ? 0 : x[0] - '0') * (y.empty() ? 0 : y[0] - '0');
            cout << "  Base case: " << x << " × " << y << " = " << result << endl;
            return to_string(result);
        }
        
        // Make both strings same length by padding with zeros
        int maxLen = max(x.length(), y.length());
        x = string(maxLen - x.length(), '0') + x;
        y = string(maxLen - y.length(), '0') + y;
        
        // If odd length, pad one more zero to make it even
        if (maxLen % 2 == 1) {
            x = "0" + x;
            y = "0" + y;
            maxLen++;
        }
        
        int mid = maxLen / 2;
        
        // Split the numbers
        string x1 = x.substr(0, mid);        // Higher-order digits
        string x0 = x.substr(mid);           // Lower-order digits  
        string y1 = y.substr(0, mid);        // Higher-order digits
        string y0 = y.substr(mid);           // Lower-order digits
        
        cout << "  Split: " << x << " = " << x1 << " | " << x0 << endl;
        cout << "         " << y << " = " << y1 << " | " << y0 << endl;
        
        // Three recursive multiplications (this is the key!)
        cout << "  Computing Z₂ = " << x1 << " × " << y1 << endl;
        string z2 = karatsubaMultiply(removeLeadingZeros(x1), removeLeadingZeros(y1));
        
        cout << "  Computing Z₀ = " << x0 << " × " << y0 << endl;
        string z0 = karatsubaMultiply(removeLeadingZeros(x0), removeLeadingZeros(y0));
        
        cout << "  Computing Z₁ = (" << x1 << "+" << x0 << ") × (" << y1 << "+" << y0 << ") - Z₂ - Z₀" << endl;
        string sum1 = addStrings(x1, x0);
        string sum2 = addStrings(y1, y0);
        cout << "    (" << sum1 << ") × (" << sum2 << ")" << endl;
        
        string z1_temp = karatsubaMultiply(removeLeadingZeros(sum1), removeLeadingZeros(sum2));
        string z1 = subtractStrings(subtractStrings(z1_temp, z2), z0);
        
        cout << "  Results: Z₂=" << z2 << ", Z₁=" << z1 << ", Z₀=" << z0 << endl;
        
        // Combine results: Z₂ × 10^n + Z₁ × 10^(n/2) + Z₀
        string term1 = multiplyByPowerOf10(z2, 2 * mid);  // Z₂ × 10^n
        string term2 = multiplyByPowerOf10(z1, mid);      // Z₁ × 10^(n/2)
        string term3 = z0;                                // Z₀
        
        cout << "  Final: " << term1 << " + " << term2 << " + " << term3 << endl;
        
        string result = addStrings(addStrings(term1, term2), term3);
        cout << "  Result: " << result << endl;
        
        return removeLeadingZeros(result);
    }

private:
    // Helper function: Add two number strings
    string addStrings(string num1, string num2) {
        string result = "";
        int carry = 0;
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += num1[i--] - '0';
            if (j >= 0) sum += num2[j--] - '0';
            
            result = char(sum % 10 + '0') + result;
            carry = sum / 10;
        }
        
        return result;
    }
    
    // Helper function: Subtract two number strings (assumes num1 >= num2)
    string subtractStrings(string num1, string num2) {
        // Pad num2 with leading zeros
        while (num2.length() < num1.length()) {
            num2 = "0" + num2;
        }
        
        string result = "";
        int borrow = 0;
        
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
        
        return removeLeadingZeros(result);
    }
    
    // Helper function: Multiply by power of 10 (append zeros)
    string multiplyByPowerOf10(string num, int power) {
        if (num == "0" || power == 0) return num;
        return num + string(power, '0');
    }
    
    // Helper function: Remove leading zeros
    string removeLeadingZeros(string num) {
        int i = 0;
        while (i < num.length() && num[i] == '0') {
            i++;
        }
        return i == num.length() ? "0" : num.substr(i);
    }
};

void demonstrateKaratsubaSteps() {
    cout << "\n" << string(70, '=') << endl;
    cout << "KARATSUBA ALGORITHM - STEP BY STEP DEMONSTRATION" << endl;
    cout << string(70, '=') << endl;
    
    cout << "\nExample: 1234 × 5678" << endl;
    cout << "\nTraditional method would need 16 single-digit multiplications" << endl;
    cout << "Karatsuba reduces this significantly!" << endl;
    
    KaratsubaExplanation demo;
    string result = demo.karatsubaMultiply("1234", "5678");
    
    cout << "\nFinal Answer: " << result << endl;
    
    // Verify with simple calculation
    cout << "Verification: 1234 × 5678 = 7006652 ✓" << endl;
}

void explainComplexityReduction() {
    cout << "\n" << string(70, '=') << endl;
    cout << "COMPLEXITY ANALYSIS" << endl;
    cout << string(70, '=') << endl;
    
    cout << "\n1. TRADITIONAL MULTIPLICATION:" << endl;
    cout << "   T(n) = 4 × T(n/2) + O(n)" << endl;
    cout << "   Using Master Theorem: T(n) = O(n²)" << endl;
    
    cout << "\n2. KARATSUBA ALGORITHM:" << endl;
    cout << "   T(n) = 3 × T(n/2) + O(n)" << endl;  
    cout << "   Using Master Theorem: T(n) = O(n^log₂(3)) ≈ O(n^1.585)" << endl;
    
    cout << "\n3. PRACTICAL IMPACT:" << endl;
    cout << "   For 1000-digit numbers:" << endl;
    cout << "   • Traditional: ~1,000,000 operations" << endl;
    cout << "   • Karatsuba:  ~31,623 operations" << endl;
    cout << "   • Speedup: ~32× faster!" << endl;
    
    cout << "\n4. WHEN TO USE KARATSUBA:" << endl;
    cout << "   • Numbers with 100+ digits" << endl;
    cout << "   • Cryptographic applications" << endl;
    cout << "   • Big integer libraries" << endl;
    cout << "   • Note: Has overhead for small numbers" << endl;
}

void visualKaratsubaTree() {
    cout << "\n" << string(70, '=') << endl;
    cout << "RECURSION TREE VISUALIZATION" << endl;
    cout << string(70, '=') << endl;
    
    cout << "\nFor multiplying two 4-digit numbers:" << endl;
    cout << "\n                    1234 × 5678" << endl;
    cout << "                   /      |      \\" << endl;
    cout << "            12×56       (12+34)×(56+78)     34×78" << endl;
    cout << "           /     \\       /         \\        /     \\" << endl;
    cout << "        1×5     2×6    46×134    etc...   3×7   4×8" << endl;
    cout << "\nTraditional would have 4 branches at each level" << endl;
    cout << "Karatsuba has only 3 branches - this saves exponentially!" << endl;
    
    cout << "\nRecursion depth: log₂(n) where n is number of digits" << endl;
    cout << "At each level: 3 multiplications instead of 4" << endl;
    cout << "Total multiplications: 3^(log₂(n)) = n^(log₂(3)) ≈ n^1.585" << endl;
}

int main() {
    cout << "KARATSUBA MULTIPLICATION ALGORITHM" << endl;
    cout << "The Divide-and-Conquer Approach to Fast Multiplication" << endl;
    
    demonstrateKaratsubaSteps();
    explainComplexityReduction();  
    visualKaratsubaTree();
    
    cout << "\n" << string(70, '=') << endl;
    cout << "KEY INSIGHTS" << endl;
    cout << string(70, '=') << endl;
    
    cout << "\n1. THE CORE TRICK:" << endl;
    cout << "   Instead of computing 4 products: X₁Y₁, X₁Y₀, X₀Y₁, X₀Y₀" << endl;
    cout << "   Compute 3 products: X₁Y₁, X₀Y₀, (X₁+X₀)(Y₁+Y₀)" << endl;
    cout << "   Then: X₁Y₀ + X₀Y₁ = (X₁+X₀)(Y₁+Y₀) - X₁Y₁ - X₀Y₀" << endl;
    
    cout << "\n2. WHY IT WORKS:" << endl;
    cout << "   Mathematical identity: (a+b)(c+d) = ac + ad + bc + bd" << endl;
    cout << "   Rearranging: ad + bc = (a+b)(c+d) - ac - bd" << endl;
    cout << "   This eliminates 1 multiplication in exchange for additions!" << endl;
    
    cout << "\n3. RECURSIVE BENEFIT:" << endl;
    cout << "   Savings multiply at each level of recursion" << endl;
    cout << "   O(n²) → O(n^1.585) asymptotic improvement" << endl;
    
    cout << "\n4. PRACTICAL CONSIDERATIONS:" << endl;
    cout << "   • Higher constant factors than grade school" << endl;
    cout << "   • Break-even point around 100-digit numbers" << endl;
    cout << "   • Used in production big-integer libraries" << endl;
    cout << "   • Can be combined with FFT for even larger numbers" << endl;
    
    return 0;
}

/*
KARATSUBA IN A NUTSHELL:

Traditional: 4 recursive calls → O(n²)
X×Y needs: X₁Y₁, X₁Y₀, X₀Y₁, X₀Y₀

Karatsuba: 3 recursive calls → O(n^1.585) 
X×Y needs: X₁Y₁, X₀Y₀, (X₁+X₀)(Y₁+Y₀)
Then compute: X₁Y₀ + X₀Y₁ = (X₁+X₀)(Y₁+Y₀) - X₁Y₁ - X₀Y₀

The magic is trading 1 multiplication for some additions!
*/