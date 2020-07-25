package parallel.lab2;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

public class Consumer implements Runnable {
    private BlockingQueue<Task> q1;
    private BlockingQueue<Task> q2;
    private String threadId;

    public Consumer(BlockingQueue<Task> q1, BlockingQueue<Task> q2) {
        this.q1 = q1;
        this.q2 = q2;
    }

    public void run() {
        threadId = "Consumer-" + Thread.currentThread().getId();
        try {
            while (true) {
                Task task1 = q1.poll(1, TimeUnit.SECONDS);

                if (task1 != null) {
                    consume(task1, "1");
                } else {
                    Task task2 = q2.poll(1, TimeUnit.SECONDS);

                    if (task2 != null) {
                        consume(task2, "2");
                    } else {
                        break;
                    }

                }
            }

            System.out.println("\n" + threadId + " STOPPED.\n");
        } catch (InterruptedException ie) {
            ie.printStackTrace();
        }
    }

    private void consume(Task task, String type) throws InterruptedException {
        System.out.printf("%s: Consuming a task number %s of type %s\n", threadId, task.id, type);
        Thread.sleep(task.timeToComplete);
    }
}
