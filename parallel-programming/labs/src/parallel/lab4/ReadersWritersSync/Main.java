package parallel.lab4.ReadersWritersSync;

public class Main {

    public static void main(String[] args) {
        final int READERS = 2;
        final int WRITERS = 1;
        Database database = new Database();

        for (int i = 0; i < READERS; i++) new Reader(database).start();
        for (int i = 0; i < WRITERS; i++) new Writer(database).start();
    }
}