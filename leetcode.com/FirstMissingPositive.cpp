class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; i++) {
	    while (0 <= nums[i] - 1 && nums[i] - 1 < n && nums[i] != i + 1 && nums[nums[i] - 1] != nums[i]) {
		swap(nums[i], nums[nums[i] - 1]);
	    }
	}
	for (int i = 0; i < n; i++)
	    if (nums[i] != i + 1) return i + 1;

	return n + 1;
    }
};
