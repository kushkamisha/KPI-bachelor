package parallel.lab4.ReadersWritersSemaphore;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class Database {
    AtomicInteger readers;

    public Database() {
        this.readers = new AtomicInteger(0);
    }

    public void read(Semaphore sm) {
        this.readers.incrementAndGet();
        System.out.println("Reader " + Thread.currentThread().getName() + " starts READING.");

        final int DELAY = 100;
        try { Thread.sleep((int) (Math.random() * DELAY)); }
        catch (InterruptedException e) { e.printStackTrace(); }

        System.out.println("Reader " + Thread.currentThread().getName() + " stops READING.");
        this.readers.decrementAndGet();
        if (this.readers.get() == 0) {
            sm.release();
        }
    }

    public void write(Semaphore sm) {
        System.out.println("Writer " + Thread.currentThread().getName() + " starts WRITING.");

        final int DELAY = 1000;
        try { Thread.sleep((int) (Math.random() * DELAY)); }
        catch (InterruptedException e) { e.printStackTrace(); }

        System.out.println("Writer " + Thread.currentThread().getName() + " stops WRITING.");
        sm.release();
    }
}