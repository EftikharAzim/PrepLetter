#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <numeric>
using namespace std;

/**
 * @class Solution
 * @brief Provides a unified method to compute the closest sum of k elements in a vector.
 *
 * Thought Process:
 * The kSum Closest problem is a generalization of the well-known 3Sum Closest.
 * The approach relies on recursion:
 * - For k > 2, we recursively fix one number and reduce the problem to (k-1)Sum Closest.
 * - When k == 2, we solve it using the classic two-pointer technique, which efficiently finds the two numbers closest to a remaining target.
 * Throughout the recursion, we maintain the smallest difference between the sum and target,
 * updating our result whenever a closer sum is found.
 */
class Solution
{
public:
    /**
     * @brief Finds the closest sum of 3 integers in nums to the target.
     *
     * @param nums Vector of integers.
     * @param target Target sum to approximate.
     * @return Closest sum of 3 integers to the target.
     *
     * Delegates to kSumClosest with k = 3.
     */
    int threeSumClosest(vector<int> &nums, int target)
    {
        return kSumClosest(nums, target, 3);
    }

    /**
     * @brief Finds the closest sum of k integers in nums to the target.
     *
     * @param nums Vector of integers.
     * @param target Target sum to approximate.
     * @param k Number of elements in the sum.
     * @return Closest sum of k integers to the target.
     *
     * Thought Process:
     * The algorithm starts by sorting the array to enable efficient two-pointer traversal for the 2Sum case.
     * It then recursively chooses an element and reduces the kSum problem to (k-1)Sum.
     * At the base case of k == 2, a two-pointer approach is used to find the closest sum of two elements.
     * The closest difference to the target is tracked across all recursive branches.
     */
    int kSumClosest(vector<int> &nums, int target, int k)
    {
        sort(nums.begin(), nums.end());
        result = 0;
        closestDiff = INT_MAX;
        helper(nums, 0, k, target, 0);
        return result;
    }

private:
    int result;         // Closest sum found so far
    int closestDiff;    // Minimum absolute difference from the target

    /**
     * @brief Recursive helper to compute closest kSum.
     *
     * @param nums Sorted input array.
     * @param start Current index to consider elements from.
     * @param k Number of elements left to select.
     * @param target Remaining target to match.
     * @param currentSum Accumulated sum so far.
     *
     * Thought Process:
     * - For k == 2, apply the two-pointer approach from both ends of the array to find the pair
     *   whose sum is closest to the target.
     * - For k > 2, fix one element and recursively solve the (k-1)Sum problem on the remaining array.
     * - Skip duplicates to avoid redundant computations.
     * - At every valid configuration, if the new sum is closer to the target than previous ones,
     *   update the result.
     */
    void helper(const vector<int> &nums, int start, int k, int target, int currentSum)
    {
        int n = nums.size();

        // Base case: 2Sum Closest using two pointers
        if (k == 2)
        {
            int left = start;
            int right = n - 1;
            while (left < right)
            {
                int sum = nums[left] + nums[right];
                int total = currentSum + sum;
                int diff = abs(target - total);

                if (diff < closestDiff)
                {
                    closestDiff = diff;
                    result = total;
                }

                if (total < target)
                    ++left;
                else
                    --right;
            }
            return;
        }

        // Recursive case
        for (int i = start; i <= n - k; ++i)
        {
            if (i > start && nums[i] == nums[i - 1])
                continue; // skip duplicates

            helper(nums, i + 1, k - 1, target, currentSum + nums[i]);
        }
    }
};