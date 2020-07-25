package parallel.lab4.ReadersWritersSemaphore;

import java.util.concurrent.Semaphore;

public class Main {

    private static Semaphore sm = new Semaphore(2, true);

    public static void main(String[] args) {
        final int READERS = 2;
        final int WRITERS = 1;
        Database database = new Database();

        for (int i = 0; i < READERS; i++) new Reader(database, sm).start();
        for (int i = 0; i < WRITERS; i++) new Writer(database, sm).start();
    }
}