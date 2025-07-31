#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/**
 * @class Solution
 * @brief Provides a method to find the sum of three integers in an array
 *        that is closest to a given target.
 */
class Solution
{
public:
    /**
     * @brief Finds the sum of three integers in nums such that the sum is closest to the given target.
     *
     * @param nums A vector of integers
     * @param target An integer target to approximate
     * @return The sum of the triplet closest to the target
     *
     * @details
     * Approach:
     * - First sort the array to apply the two-pointer technique.
     * - For each index i, use two pointers (left, right) to find the pair whose sum with nums[i] is closest to target.
     * - Update the closest sum whenever a smaller absolute difference is found.
     * - If exact match is found (sum == target), return immediately.
     *
     * Time Complexity: O(n^2)
     *   - Sorting the array takes O(n log n)
     *   - Two nested loops over n elements result in O(n^2) overall
     *
     * Space Complexity: O(1)
     *   - No extra space is used beyond a few scalar variables
     */
    int threeSumClosest(vector<int> &nums, int target)
    {
        int n = nums.size();
        if (n < 3) return 0;

        // Initialize variables to track the closest gap and sum found so far
        int closestGap = INT_MAX;
        int closestSum = 0;

        // Sort to enable two-pointer technique
        sort(nums.begin(), nums.end());

        // Iterate through the array, fixing one element at a time
        for (int i = 0; i < n - 2; ++i)
        {
            int left = i + 1;
            int right = n - 1;

            // Use two-pointer traversal to find the closest sum for this i
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];

                // If exact match, return immediately
                if (sum == target)
                {
                    return sum;
                }

                // Update closest sum if current is closer to target
                if (abs(sum - target) < closestGap)
                {
                    closestGap = abs(sum - target);
                    closestSum = sum;
                }

                // Move pointers based on comparison with target
                if (sum > target)
                {
                    --right;
                }
                else
                {
                    ++left;
                }
            }
        }

        return closestSum;
    }
};