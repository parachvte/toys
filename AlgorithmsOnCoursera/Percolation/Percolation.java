public class Percolation {
    private static final int[] DX = {-1, 0, 1, 0}; // directory
    private static final int[] DY = {0, -1, 0, 1};

    private int n, virtualTop, virtualBottom;
    private boolean[] grids;
    private WeightedQuickUnionUF unionFind;
    private WeightedQuickUnionUF fullUnionFind;
    
    /**
     * create N-by-N grid, with all sites blocked
     */
    public Percolation(int n) {
        this.n = n;
        virtualTop = 0;
        virtualBottom = n * n + 1;
        grids = new boolean[n * n + 1];
        unionFind = new WeightedQuickUnionUF(n * n + 2);
        fullUnionFind = new WeightedQuickUnionUF(n * n + 1);
    }
    
    /**
     * open site (row i, column j) if it is not alreaDY
     */
    public void open(int i, int j) {
        if (isOpen(i, j)) return;
        grids[index(i, j)] = true;
        for (int d = 0; d < 4; d++) {
            int i2 = i + DX[d];
            int j2 = j + DY[d];
            if (outOfRange(i2, j2, false)) {
                if (i2 < 1) {
                    unionFind.union(index(i, j), virtualTop);
                    fullUnionFind.union(index(i, j), virtualTop);
                }
                if (i2 > n)
                    unionFind.union(index(i, j), virtualBottom);
                continue;
            }
            if (isOpen(i2, j2)) {
                unionFind.union(index(i, j), index(i2, j2));
                fullUnionFind.union(index(i, j), index(i2, j2));
            }
        }
    }
    
    /**
     * check if site (row i, column j) is open
     */
    public boolean isOpen(int i, int j) {
        outOfRange(i, j, true);
        return grids[index(i, j)];
    }
    
    /**
     * check if site (row i, column j) is full
     */
    public boolean isFull(int i, int j) {
        outOfRange(i, j, true);
        return fullUnionFind.connected(virtualTop, index(i, j));
    }
    
    /**
     * does the system percolate?
     */
    public boolean percolates() {
        return unionFind.connected(virtualTop, virtualBottom);
    }
    
    /**
     * return index of (i, j)
     */
    private int index(int i, int j) {
        return (i - 1) * n + j;
    }
    
    /**
     * check if (i, j) is out of range [1, n] * [1, n]
     * if yes, and throwExp is true, then throw java.lang.IndexOutOfBoundsException
     */
    private boolean outOfRange(int i, int j, boolean throwExp) {
        if (i < 1 || i > n || j < 1 || j > n) {
            if (throwExp) throw new java.lang.IndexOutOfBoundsException("(row i, column j) out of range.");
            return true;
        } else
            return false;
    }
}