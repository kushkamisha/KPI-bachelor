package parallel.lab4.SleepingBarber;

import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicInteger;

class Main {

    private static AtomicInteger numOfFreeWRSeats;
    private static Semaphore barberReady;
    private static Semaphore customers;

    public static void main(String[] args) {
        numOfFreeWRSeats = new AtomicInteger(3);
        barberReady = new Semaphore(0, true);
        customers = new Semaphore(0, true);

        new Thread(new Barber(barberReady, customers)).start();

        while(true) {
            try {
                Thread.sleep(ThreadLocalRandom.current().nextInt(100, 1000 + 100));
            } catch (InterruptedException e) {}

            System.out.println("A new customer walks in");
            new Thread(new Customer(numOfFreeWRSeats, barberReady, customers)).start();
        }
    }
}
