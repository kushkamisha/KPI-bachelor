package parallel.lab4.ReadersWritersSync;

public class Writer extends Thread {
    private Database database;

    public Writer(Database database) {
        super();
        this.database = database;
    }

    public void run() {
        while (true) {
            final int DELAY = 500;
            try { Thread.sleep((int) (Math.random() * DELAY)); }
            catch (InterruptedException e) { e.printStackTrace(); }
            database.write();
        }
    }
}
