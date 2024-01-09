#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != val) {
                ++ans;
            } else {
                int fast = i + 1;
                for (; fast < nums.size(); ++fast) {
                    if (nums[fast] != val) {
                        std::swap(nums[i], nums[fast]);
                        ++ans;
                        break;
                    }
                    if (fast == nums.size() - 1)
                        return ans;
                }
            }
        }
        return ans;
    }
};

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::vector<int> nums, ans;
        int tem, len, left = 0, right;
        std::cin >> len;
        for (int k = 0; k < len; ++k) {
            std::cin >> tem;
            nums.push_back(tem);
        }
        right = nums.size() - 1;
        while (left <= right) {
            ans.push_back(nums[left]);
            if (left == right)
                break;
            ans.push_back(nums[right]);
            ++left;
            --right;
        }
        for (int k = 0; k < len; ++k)
            std::cout << ans[k] << " ";
    }
}
