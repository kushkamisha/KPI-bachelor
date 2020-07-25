package parallel.lab4.ReadersWritersSync;

public class Database {
    private int readers;

    public Database() {
        this.readers = 0;
    }

    public void read() {
        synchronized(this) {
            this.readers++;
            System.out.println("Reader " + Thread.currentThread().getName() + " starts READING.");
        }

        final int DELAY = 500;
        try { Thread.sleep((int) (Math.random() * DELAY)); }
        catch (InterruptedException e) { e.printStackTrace(); }

        synchronized(this) {
            System.out.println("Reader " + Thread.currentThread().getName() + " stops READING.");
            this.readers--;
            if (this.readers == 0) {
                this.notifyAll();
            }
        }
    }

    public synchronized void write() {
        while (this.readers != 0) {
            try { this.wait(); }
            catch (InterruptedException e) { e.printStackTrace(); }
        }

        System.out.println("Writer " + Thread.currentThread().getName() + " starts WRITING.");

        final int DELAY = 2000;
        try { Thread.sleep((int) (Math.random() * DELAY)); }
        catch (InterruptedException e) { e.printStackTrace(); }

        System.out.println("Writer " + Thread.currentThread().getName() + " stops WRITING.");
        this.notifyAll();
    }
}