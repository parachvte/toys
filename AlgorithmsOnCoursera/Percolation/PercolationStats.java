public class PercolationStats {
    private int n, t;
    private double[] fractions; // fraction of open sites
    
    /**
     * perform T independent computational experiments on an N-by-N grid
     */
    public PercolationStats(int n, int t) {
        if (n <= 0 || t <= 0) {
            throw new java.lang.IllegalArgumentException();
        }
        this.n = n;
        this.t = t;
        fractions = new double[t];
        for (int i = 0; i < t; i++) run(i);
    }
    
    /**
     * To run the experiment
     */
    private void run(int testId) {
        Percolation perco = new Percolation(n);
        for (int i = 0; i < n * n; ) {
            int x = StdRandom.uniform(n) + 1;
            int y = StdRandom.uniform(n) + 1;
            if (!perco.isOpen(x, y)) {
                perco.open(x, y);
                i++;
            }
            if (perco.percolates()) {
                fractions[testId] = (double)(i) / (n * n);
                return;
            }
        }
    }
    
    /**
     * sample mean of percolation threshold
     */
    public double mean() {
        return StdStats.mean(fractions);
    }
    
    /**
     * sample standard deviation of percolation threshold
     */
    public double stddev() {
        return StdStats.stddev(fractions);
    }
    
    /**
     * returns lower bound of the 95% confidence interval
     */
    public double confidenceLo() {
        return mean() - 1.96 * stddev() / Math.sqrt(t);
    }
    
    /**
     * returns upper bound of the 95% confidence interval
     */
    public double confidenceHi() {
        return mean() + 1.96 * stddev() / Math.sqrt(t);
    }
    
    /**
     * test client, described below
     */
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int t = Integer.parseInt(args[1]);
        StdOut.printf("N = %d T = %d\n", n, t);
        PercolationStats ps = new PercolationStats(n, t);
        StdOut.printf("mean                    = %.6f\n", ps.mean());
        StdOut.printf("stddev                  = %.18f\n", ps.stddev());
        StdOut.printf("95%% confidence interval = %.16f, %.16f\n", ps.confidenceLo(), ps.confidenceHi());
    }
}