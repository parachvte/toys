class Solution {
    public:
        bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
            multiset<int> S;
            multiset<int>::iterator it, prev, succ;

            int n = nums.size();
            for (int i = 0; i < n; i++) {
                int j;
                if ((j = i - k - 1) >= 0) {
                    it = S.lower_bound(nums[j]);
                    S.erase(it);
                }

                S.insert(nums[i]);
                it = S.lower_bound(nums[i]);

                if (it != S.begin()) {
                    prev = it; prev--;
                    if (nums[i] - *prev <= t) return true;
                }

                succ = it; succ++;
                if (succ != S.end()) {
                    if (*succ - nums[i] <= t) return true;
                }
            }

            return false;
        }
};
