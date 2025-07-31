// https://leetcode.com/problems/container-with-most-water/description/
// Problem: Container With Most Water (LeetCode 11)
// Given an array 'height' of non-negative integers representing vertical lines on the x-axis,
// the task is to find two lines that together with the x-axis form a container such that the container contains the most water.
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @class Solution
 * @brief Solves the "Container With Most Water" problem using a two-pointer approach.
 */
class Solution
{
public:
    /**
     * @brief Calculates the maximum area of water a container can hold.
     *
     * @param height A vector of non-negative integers representing the heights of vertical lines.
     * @return The maximum amount of water that can be contained.
     *
     * @details
     * The algorithm uses two pointers starting at both ends of the array and moves them toward each other.
     * At each step, it calculates the area formed between the two pointers and updates the maximum area.
     * The pointer with the shorter height is moved inward in hopes of finding a taller line and potentially a larger area.
     *
     * Time Complexity: O(n) - each element is visited at most once.
     * Space Complexity: O(1) - constant extra space is used.
     */
    int maxArea(vector<int> &height)
    {
        int n = height.size();
        int left = 0;
        int right = n - 1;
        int maxArea = 0;

        // Use two pointers to evaluate potential containers
        while (left < right)
        {
            // Calculate area formed between the two lines
            int area = min(height[right], height[left]) * (right - left);

            // Update maxArea if this container holds more water
            if (area > maxArea)
            {
                maxArea = area;
            }

            // Move the pointer with the shorter height inward
            if (height[left] < height[right])
            {
                left++;
            }
            else
            {
                right--;
            }
        }

        return maxArea;
    }
};