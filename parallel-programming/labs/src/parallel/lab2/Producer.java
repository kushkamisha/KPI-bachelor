package parallel.lab2;

import java.util.concurrent.BlockingQueue;

//import static java.lang.Math.random;

public class Producer implements Runnable {
    private BlockingQueue<Task> queue;
    private String threadId;
    private String type;
    private Integer maxQLen;

    public Producer (BlockingQueue<Task> queue, String type) {
        this.queue = queue;
        this.type = type;
        this.maxQLen = 0;
    }

    public void run() {
        threadId = "Producer-" + Thread.currentThread().getId();

        try {
            for (int i = 0; i < 5; i++) {
                queue.put(produce(i));
                if (queue.size() > maxQLen) maxQLen = queue.size();
//                Thread.sleep(500);
            }

            System.out.println("\n" + threadId + ": Producer STOPPED.\n");
            System.out.printf("Max len of Q of type %s is %d\n", type, maxQLen);

        } catch (InterruptedException ie) {
            ie.printStackTrace();
        }
    }

    private Task produce(int id) {
        Task task = new Task(id, (int) (Math.random() * 100));
        System.out.printf("%s: Producing a task number %s of type %s\n", threadId, task.id, type);
        return task;
    }
}

