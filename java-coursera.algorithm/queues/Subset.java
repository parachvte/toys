public class Subset {
    public static void main(String[] args) {
        int k = Integer.parseInt(args[0]);
        String[] input = StdIn.readLine().split(" ");
        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        for (String s: input) rq.enqueue(s);
        for (int i = 0; i < k; i++) StdOut.println(rq.dequeue());
    }
}