class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        vector<int> clear_row(n);
        vector<int> clear_col(m);
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (!matrix[i][j]) clear_row[i] = 1, clear_col[j] = 1;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (clear_row[i] || clear_col[j]) matrix[i][j] = 0;
    }
};