import java.util.Scanner;

public class Main {

    static class ThreadTask implements Runnable {
        private int a, b;
        private String operation;
        private int[] intResult;
        private double[] doubleResult;

        public ThreadTask(int a, int b, String operation, int[] intResult, double[] doubleResult) {
            this.a = a;
            this.b = b;
            this.operation = operation;
            this.intResult = intResult;
            this.doubleResult = doubleResult;
        }

        @Override
        public void run() {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            switch (operation) {
                case "add":
                    intResult[0] = a + b;
                    break;
                case "subtract":
                    intResult[0] = a - b;
                    break;
                case "multiply":
                    intResult[0] = a * b;
                    break;
                case "divide":
                    if (b != 0) {
                        doubleResult[0] = (double) a / b;
                    } else {
                        System.out.println("Division by zero");
                        doubleResult[0] = 0.0;
                    }
                    break;
                case "log":
                    if (a > 0 && b > 0) {
                        doubleResult[0] = Math.log(a) / Math.log(b);
                    } else {
                        System.out.println("Numbers must be positive");
                        doubleResult[0] = 0.0;
                    }
                    break;
                case "gcd":
                    int x = a, y = b;
                    while (y != 0) {
                        int temp = y;
                        y = x % y;
                        x = temp;
                    }
                    intResult[0] = x;
                    break;
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input two numbers from the user
        System.out.print("Enter first number: ");
        int m = scanner.nextInt();
        System.out.print("Enter second number: ");
        int n = scanner.nextInt();

        // Create result containers
        final int[] addRes = {0};
        final int[] subRes = {0};
        final int[] mulRes = {0};
        final double[] divRes = {0.0};
        final double[] logRes = {0.0};
        final int[] gcdRes = {0};

        // Create threads for each operation
        Thread t1 = new Thread(new ThreadTask(m, n, "add", addRes, null));
        Thread t2 = new Thread(new ThreadTask(m, n, "subtract", subRes, null));
        Thread t3 = new Thread(new ThreadTask(m, n, "multiply", mulRes, null));
        Thread t4 = new Thread(new ThreadTask(m, n, "divide", null, divRes));
        Thread t5 = new Thread(new ThreadTask(m, n, "log", null, logRes));
        Thread t6 = new Thread(new ThreadTask(m, n, "gcd", gcdRes, null));

        // Start the threads
        t1.start();
        t2.start();
        t3.start();
        t4.start();
        t5.start();
        t6.start();

        // Wait for all threads to finish
        try {
            t1.join();
            t2.join();
            t3.join();
            t4.join();
            t5.join();
            t6.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Output results
        System.out.println("\nThe Output is: ");
        System.out.println("Addition: " + addRes[0]);
        System.out.println("Subtraction: " + subRes[0]);
        System.out.println("Multiplication: " + mulRes[0]);
        System.out.println("Division: " + divRes[0]);
        System.out.println("Logarithm of " + m + " base " + n + " is: " + logRes[0]);
        System.out.println("GCD of " + m + " and " + n + ": " + gcdRes[0]);

        scanner.close();
    }
}
