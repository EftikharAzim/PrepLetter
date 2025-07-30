// Given a sorted array of integers and a target value, find the indices(1 - based) of two numbers that add up to the target.Assume exactly one solution exists, and you cannot use the same element twice.

#include <vector>
#include <unordered_map>
using namespace std;

/**
 * Find two numbers in a sorted array that sum up to a target.
 * Returns 1-based indices of the pair. Assumes exactly one solution exists.
 * Uses two-pointer approach.
 * 
 * Time Complexity: O(n)
 * - The two pointers move at most n steps combined, with each moving inward once per iteration.
 * - No nested loops or extra passes; single pass through the array.
 * 
 * Space Complexity: O(1)
 * - Uses a constant amount of extra space (left, right, sum variables).
 * 
 * Assumptions:
 * - The input array is sorted in non-decreasing order.
 * - Exactly one solution is guaranteed by the problem statement.
 * - Indices returned are 1-based.
 */
class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int left = 0;
        int right = numbers.size() - 1;

        // Use two pointers to find the correct pair
        while (left < right)
        {
            int sum = numbers[left] + numbers[right];

            if (sum > target)
                right--; // Decrease sum
            else if (sum < target)
                left++; // Increase sum
            else
                return {left + 1, right + 1}; // Found the pair (1-based)
        }

        return {}; // Should not reach here if one solution is guaranteed
    }
};

/**
 * Logic and Assumptions:
 * - Iterates through the array, for each number checks if its complement (target - number)
 *   has already been seen (stored in the hash map).
 * - If the complement is found, returns the stored index and the current index (both 1-based).
 * - If not found, stores the current number and its index in the hash map.
 * - Assumes exactly one solution exists.
 * - Input array is not necessarily sorted.
 * - Indices returned are 1-based, as required by the problem.
 *
 * Time Complexity: O(n)
 *   - Single pass through the array.
 *   - Each lookup and insert operation in the hash map is O(1) on average.
 *
 * Space Complexity: O(n)
 *   - Stores up to n elements in the unordered_map in the worst case.
 */
class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        unordered_map<int, int> seen;

        for (int i = 0; i < numbers.size(); ++i)
        {
            int complement = target - numbers[i];

            // If the complement has already been seen, return the 1-based indices
            if (seen.count(complement))
            {
                return {seen[complement] + 1, i + 1};
            }

            // Store the current number with its index
            seen[numbers[i]] = i;
        }

        return {}; // Should not reach here if one solution is guaranteed
    }
};