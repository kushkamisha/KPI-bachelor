package parallel.lab4.SleepingBarber;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class Customer implements Runnable {

    private AtomicInteger numOfFreeWRSeats;
    private Semaphore barberReady;
    private Semaphore custReady;

    public Customer(AtomicInteger numOfFreeWRSeats, Semaphore barberReady, Semaphore cavailable) {
        this.numOfFreeWRSeats = numOfFreeWRSeats;
        this.barberReady = barberReady;
        this.custReady = cavailable;
    }

    public void run() {
        try {
            if (numOfFreeWRSeats.get() < 0) {
                System.out.println("Customer is left without a haircut");
                return;
            }
            custReady.release();
            if (barberReady.hasQueuedThreads()) {
                numOfFreeWRSeats.decrementAndGet();
                System.out.println("A customer is waiting...");
                barberReady.acquire();
                numOfFreeWRSeats.incrementAndGet();
            } else {
                barberReady.acquire();
            }

        } catch (InterruptedException e) {}
    }
}
