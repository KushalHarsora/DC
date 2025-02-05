import java.util.Random;

class ClockSynchronization {
    private int localClock;

    public ClockSynchronization() {
        this.localClock = new Random().nextInt(100); // Initialize with a random clock value
    }

    public synchronized void updateClock(int receivedTime) {
        localClock = Math.max(localClock, receivedTime) + 1;
        System.out.println("Updated local clock: " + localClock);
    }

    public synchronized int getLocalClock() {
        return localClock;
    }
}

public class LamportAlgorithm {
    public static void main(String[] args) {
        ClockSynchronization process1 = new ClockSynchronization();
        ClockSynchronization process2 = new ClockSynchronization();

        System.out.println("Initial Clocks:");
        System.out.println("Process 1 Clock: " + process1.getLocalClock());
        System.out.println("Process 2 Clock: " + process2.getLocalClock());

        int timeFromProcess1 = process1.getLocalClock();
        process2.updateClock(timeFromProcess1);
    }
}
