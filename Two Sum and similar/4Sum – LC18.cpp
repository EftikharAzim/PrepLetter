// Given an array of integers and a target value, find all unique quadruplets(four numbers) in the array that add up to the target.
// Each Two Sum and similar quadruplet must not repeat in the result set.

//Example Input : nums = [ 1, 0, -1, 0, -2, 2 ], target = 0 
// Output : [ [ -2, -1, 1, 2 ], [ -2, 0, 0, 2 ], [ -1, 0, 0, 1 ] ]


#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    /**
     * Approach:
     * - Sort the array to apply two-pointer technique and handle duplicates.
     * - Fix two numbers using nested loops (`i` and `j`).
     * - Use two pointers (`left` and `right`) to find the remaining two numbers.
     * - Skip duplicates at each level to avoid repeating quadruplets.
     * - Add valid combinations directly to the result vector.
     *
     * Time Complexity: O(n^3)
     * - Outer loop runs O(n), inner loop O(n), and two-pointer scan O(n)
     * - Total is O(n^3)
     *
     * Space Complexity: O(k)
     * - Sorting is O(log n) space in-place (not counting result)
     * - Result vector stores up to k quadruplets
     *
     * Assumptions and Constraints:
     * - Input array may contain negative, zero, and positive integers.
     * - Quadruplets must not repeat in the result.
     * - Handles possible integer overflow by using long long for sum calculation.
     * - Input size n may be up to a few hundred (practical for O(n^3)).
     */
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        vector<vector<int>> result;
        int n = nums.size();

        if (n < 4)
            return result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; ++i)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue; // Skip duplicates

            for (int j = i + 1; j < n - 2; ++j)
            {
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue; // Skip duplicates

                int left = j + 1, right = n - 1;

                while (left < right)
                {
                    long long sum = static_cast<long long>(nums[i]) + nums[j] +
                                    nums[left] + nums[right];

                    if (sum == target)
                    {
                        result.push_back(
                            {nums[i], nums[j], nums[left], nums[right]});

                        // Skip duplicates for left and right
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
        }
        return result;
    }

    /**
     * Optimized hash map approach to find unique quadruplets that sum to the target.
     *
     * Approach:
     * - Use a hash map to store all pair sums and their indices.
     * - For every new pair, check if (target - current sum) exists in the map.
     * - Avoid using the same index in a quadruplet.
     * - Sort each valid quadruplet before adding to results to handle duplicates.
     * - Use a set or inlined deduplication to avoid result duplicates.
     *
     * Time Complexity: O(n^2 * k) where k is average pairs per sum bucket.
     * Space Complexity: O(n^2) for the hash map of pairs.
     */
    vector<vector<int>> fourSumHashMap(vector<int>& nums, int target) {
        unordered_map<int, vector<pair<int, int>>> pairSum;
        vector<vector<int>> result;
        set<vector<int>> seen;  // For deduplication
        int n = nums.size();

        if (n < 4)
            return result;

        sort(nums.begin(), nums.end());

        // Build all pair sums
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int sum = nums[i] + nums[j];
                pairSum[sum].push_back({i, j});
            }
        }

        // Check combinations
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int remain = target - nums[i] - nums[j];
                if (pairSum.count(remain)) {
                    for (auto& [k, l] : pairSum[remain]) {
                        if (j < k) {  // Ensure all indices are unique and in order
                            vector<int> quad = {nums[i], nums[j], nums[k], nums[l]};
                            sort(quad.begin(), quad.end());
                            if (seen.insert(quad).second) {
                                result.push_back(quad);
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

    /**
     * Optimized hash map approach for fourSum using deduplication keys instead of set.
     *
     * - Avoids sorting each quadruplet.
     * - Avoids set<vector<int>>; uses unordered_set<string> for deduplication.
     * - Faster insertions and reduced TLE risk.
     *
     * Critical Test Case: nums = [2,2,2,2,2], target = 8
     * - Only one valid quadruplet: [2,2,2,2]
     * - Code must avoid duplicates despite repeated elements.
     */
    vector<vector<int>> fourSumHashMapOptimized(vector<int>& nums, int target) {
        unordered_map<int, vector<pair<int, int>>> pairSum;
        unordered_set<string> seenKeys;
        vector<vector<int>> result;
        int n = nums.size();

        if (n < 4) return result;
        sort(nums.begin(), nums.end());

        // Store all pair sums
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int sum = nums[i] + nums[j];
                pairSum[sum].emplace_back(i, j);
            }
        }

        // Check combinations and avoid duplicates
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int remain = target - nums[i] - nums[j];
                if (pairSum.count(remain)) {
                    for (auto& [k, l] : pairSum[remain]) {
                        if (j < k) { // Ensure indices are ordered and not reused
                            vector<int> quad = {nums[i], nums[j], nums[k], nums[l]};
                            // Generate a unique key for deduplication
                            string key = to_string(nums[i]) + "#" + to_string(nums[j]) + "#" +
                                         to_string(nums[k]) + "#" + to_string(nums[l]);
                            if (seenKeys.insert(key).second) {
                                result.push_back(quad);
                            }
                        }
                    }
                }
            }
        }

        return result;
    }
};