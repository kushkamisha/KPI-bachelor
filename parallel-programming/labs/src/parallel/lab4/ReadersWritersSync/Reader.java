package parallel.lab4.ReadersWritersSync;

public class Reader extends Thread {
    private Database database;

    public Reader(Database database) {
        super();
        this.database = database;
    }

    public void run() {
        while (true) {
            final int DELAY = 500;
            try { Thread.sleep((int) (Math.random() * DELAY)); }
            catch (InterruptedException e) { e.printStackTrace(); }
            this.database.read();
        }
    }
}