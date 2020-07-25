package parallel.lab4.SleepingBarber;

import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class Barber implements Runnable {

    private Semaphore barberReady;
    private Semaphore custReady;

    public Barber(Semaphore bavailable, Semaphore custReady) {
        this.barberReady = bavailable;
        this.custReady = custReady;
    }

    public void run() {
        while(true) {
            try {
                custReady.acquire();
                System.out.println("The barber is cutting hair");
                Thread.sleep(ThreadLocalRandom.current().nextInt(200, 2000 + 200));
                System.out.println("The customer has its hair cut");
                barberReady.release();

            } catch (InterruptedException e) {}
        }
    }
}
