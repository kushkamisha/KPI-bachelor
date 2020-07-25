package parallel.lab4.ReadersWritersSemaphore;

import java.util.concurrent.Semaphore;

public class Reader extends Thread {
    private Database database;
    private Semaphore sm;

    public Reader(Database database, Semaphore sm) {
        super();
        this.database = database;
        this.sm = sm;
    }

    public void run() {
        while (true) {
            try {
                sm.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
//            final int DELAY = 500;
//            try { Thread.sleep((int) (Math.random() * DELAY)); }
//            catch (InterruptedException e) { e.printStackTrace(); }
            database.read(sm);
        }
    }
}