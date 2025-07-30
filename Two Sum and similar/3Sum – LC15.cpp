// Given an array of integers, find all unique triplets(three numbers) in the array which sum to zero.The solution set must not contain duplicate triplets.

// Input : nums = [ -1, 0, 1, 2, -1, -4 ] 
// Output : [ [ -1, -1, 2 ], [ -1, 0, 1 ] ]

// Triplets must not repeat – order doesn’t matter.

#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    /**
     * Approach:
     * - Sort the array.
     * - Fix one number and use two-pointer technique for the remaining part.
     * - Skip duplicates to ensure uniqueness.
     * 
     * Time: O(n^2), Space: O(log n) for sorting
     */
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;

        // Sort the input to use two-pointer and skip duplicates
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2; ++i)
        {
            // Skip duplicate values for the first number
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int target = -nums[i];
            int left = i + 1;
            int right = nums.size() - 1;

            // Two-pointer search for the other two numbers
            while (left < right)
            {
                int curSum = nums[left] + nums[right];

                if (curSum == target)
                {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // Skip duplicates for left and right
                    while (left < right && nums[left] == nums[left + 1])
                        left++;
                    while (left < right && nums[right] == nums[right - 1])
                        right--;

                    left++;
                    right--;
                }
                else if (curSum < target)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }

        return result;
    }
};

class Solution
{
public:
    /**
     * HashSet-based approach to find all unique triplets that sum to zero.
     * 
     * Approach:
     * - Sort the array.
     * - Fix one number and use a hash set to find the remaining two numbers that sum to the target.
     * - Use a set of vectors to automatically handle duplicate triplets.
     * 
     * Time: O(n^2), Space: O(n) for hash set and result storage
     */
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        set<vector<int>> resultSet;

        // Sort array to help with duplicate triplet handling
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2; ++i)
        {
            // Skip duplicate values for the first number
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            unordered_set<int> seen;

            for (int j = i + 1; j < nums.size(); ++j)
            {
                int complement = -nums[i] - nums[j];

                if (seen.count(complement))
                {
                    vector<int> triplet = {nums[i], complement, nums[j]};
                    sort(triplet.begin(), triplet.end()); // Ensure triplet is ordered
                    resultSet.insert(triplet);
                }

                seen.insert(nums[j]);
            }
        }

        // Convert set of vectors to a vector of vectors
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
};