class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        
        vector<int> heights(size);
        vector<int> indexes(size);
        int hsize = 0;
        
        int res = 0;
        for (int i = 0; i < size; i++) {
            int h = height[i];
            while (hsize && heights[hsize - 1] <= h) {
                if (hsize > 1) {
                    res += (i - indexes[hsize - 2] - 1) * (min(heights[hsize - 2], h) - heights[hsize - 1]);
                }
                hsize--;
            }
            heights[hsize] = h;
            indexes[hsize] = i;
            hsize++;
        }
        
        return res;
    }
};
