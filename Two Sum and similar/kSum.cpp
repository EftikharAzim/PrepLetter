#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    /**
     * Recursive kSum function to find all unique k-tuples that sum up to a target.
     *
     * Approach:
     * - Sort the array beforehand.
     * - For k == 2: use the classic two-pointer approach to find pairs.
     * - For k > 2: recursively reduce the problem by fixing one number and solving (k-1)Sum.
     * - Avoid duplicates by skipping same numbers at each level.
     * - Early pruning: skip further recursion if the smallest or largest k numbers can't hit the target.
     *
     * Time Complexity:
     * - Worst-case O(n^(k-1)), due to (k-2) nested loops and two-pointer at the base.
     * - Pruning and duplicate-skipping significantly reduce practical runtime.
     *
     * Space Complexity:
     * - O(k) for recursion depth.
     * - O(output size) for storing results.
     *
     * Example:
     * - Input: nums = [1, 0, -1, 0, -2, 2], target = 0, k = 4
     * - Output: all unique quadruplets that sum to 0
     */
    vector<vector<int>> kSum(vector<int> &nums, int target, int k, int start = 0)
    {
        vector<vector<int>> res;

        if (k == 2)
        {
            // Two pointer base case
            int left = start, right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[left] + nums[right];
                if (sum == target)
                {
                    res.push_back({nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1])
                        left++;
                    while (left < right && nums[right] == nums[right - 1])
                        right--;
                    left++;
                    right--;
                }
                else if (sum < target)
                {
                    left++;
                }
                else
                {
                    right--;
                }
            }
        }
        else
        {
            for (int i = start; i < nums.size() - k + 1; ++i)
            {
                // Avoid duplicates
                if (i > start && nums[i] == nums[i - 1])
                    continue;

                // Early pruning
                if (nums[i] * k > target)
                    break;
                if (nums.back() * k < target)
                    continue;

                vector<vector<int>> temp = kSum(nums, target - nums[i], k - 1, i + 1);
                for (auto &vec : temp)
                {
                    vec.insert(vec.begin(), nums[i]);
                    res.push_back(vec);
                }
            }
        }

        return res;
    }

    /**
     * Wrapper function for 4Sum using kSum.
     * Sorts the input array and initiates kSum for k = 4.
     */
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        return kSum(nums, target, 4);
    }

    /**
     * Wrapper function for 5Sum using kSum.
     * Sorts the input array and initiates kSum for k = 5.
     */
    vector<vector<int>> fiveSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        return kSum(nums, target, 5);
    }
};