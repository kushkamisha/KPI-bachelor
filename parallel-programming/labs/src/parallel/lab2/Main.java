package parallel.lab2;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/**
 * Программа моделирует обслуживание двух потоков процессов с разными параметрами центральным процессором компьютера.
 * Для каждого потока задается своя очередь. Если очередной процесс генерируется в момент, когда процессор свободен,
 * процесс поступает на обработку на процессор, иначе процесс становится в свою очередь. Если процессор освобождается,
 * он берет на обработку процесс из первой очереди и, только в том случае, если первая очередь свободна, процессор берет
 * на обработку процесс из второй очереди. Определите максимальный размер для каждой из очередей.
 */

public class Main {
  public static void main(String[] args) {
      BlockingQueue<Task> q1 = new ArrayBlockingQueue<>(20);
      BlockingQueue<Task> q2 = new ArrayBlockingQueue<>(20);

      Thread producer1 = new Thread(new Producer(q1, "1"));
//      Thread producer2 = new Thread(new Producer(q2, "2"));
      Thread consumer = new Thread(new Consumer(q1, q2));

      consumer.start();
      try {
          Thread.sleep(500);
      } catch (InterruptedException e) {
          e.printStackTrace();
      }
      producer1.start();
//      producer2.start();
  }
}
