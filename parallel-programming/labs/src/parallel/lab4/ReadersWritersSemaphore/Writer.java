package parallel.lab4.ReadersWritersSemaphore;

import java.util.concurrent.Semaphore;

public class Writer extends Thread {
    private Database database;
    private Semaphore sm;

    public Writer(Database database, Semaphore sm) {
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
//            final int DELAY = 2000;
//            try { Thread.sleep((int) (Math.random() * DELAY)); }
//            catch (InterruptedException e) { e.printStackTrace(); }
            database.write(sm);
        }
    }
}
