/**
 * @param {number[]} nums
 * @return {boolean}
 */
var containsDuplicate = function(nums) {
    var size = nums.length;
    for (var i = 0; i < size; i++)
        for (var j = i + 1; j < size; j++) {
            if (nums[i] === nums[j]) {
                return true;
            }
        }
    return false;
};