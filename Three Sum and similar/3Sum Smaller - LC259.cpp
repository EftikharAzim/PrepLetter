
// https://www.lintcode.com/problem/3sum-smaller/description

#include <vector>
#include <algorithm>
using namespace std;

/**
 * @class Solution
 * @brief Provides a method to count triplets in an array where the sum of the triplet is less than a given target.
 */
class Solution
{
public:
    /**
     * @brief Counts the number of triplets (i, j, k) in the array such that:
     *        i < j < k and nums[i] + nums[j] + nums[k] < target.
     * 
     * @param nums A reference to a vector of integers.
     * @param target An integer representing the target sum.
     * @return The number of triplets satisfying the condition.
     * 
     * @details 
     * The approach sorts the array and for each index i, uses a two-pointer approach 
     * to find valid pairs (j, k) such that the total sum is less than the target.
     * 
     * Time Complexity: O(n^2)
     *   - Sorting takes O(n log n)
     *   - The two-pointer traversal takes O(n^2) in total for all i.
     * 
     * Space Complexity: O(1)
     *   - No extra space is used except a few variables.
     */
    int threeSumSmaller(vector<int> &nums, int target)
    {
        int n = nums.size();
        if (n < 3)
            return 0;

        int result = 0;

        // Step 1: Sort the array to allow two-pointer traversal.
        sort(nums.begin(), nums.end());

        // Step 2: Iterate through the array, fixing one number at a time.
        for (int i = 0; i < n - 2; ++i)
        {
            int left = i + 1;
            int right = n - 1;

            // Step 3: Use two pointers to find valid pairs.
            while (left < right)
            {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < target)
                {
                    // All elements between left and right form valid triplets with nums[i].
                    result += (right - left);
                    ++left;
                }
                else
                {
                    // Decrease right to try a smaller triplet sum.
                    --right;
                }
            }
        }

        return result;
    }
};