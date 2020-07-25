package parallel.lab4.DiningPhilosophers;

import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class Main {

    static int philosopher = 5;
    static philosopher philosophers[] = new philosopher[philosopher];
    static Chopstick chopsticks[] = new Chopstick[philosopher];

    static class Chopstick {

        public Semaphore mutex = new Semaphore(1);

        void grab() {
            try {
                mutex.acquire();
            }
            catch (Exception e) {
                e.printStackTrace(System.out);
            }
        }

        void release() {
            mutex.release();
        }

        boolean isFree() {
            return mutex.availablePermits() > 0;
        }

    }

    static class philosopher extends Thread {

        public int number;
        public Chopstick leftchopstick;
        public Chopstick rightchopstick;

        philosopher(int num, Chopstick left, Chopstick right) {
            number = num;
            leftchopstick = left;
            rightchopstick = right;
        }

        public void run() {

            while (true) {
                int rand = (int) Math.round(Math.random());
                if (rand == 0) {
                    leftchopstick.grab();
                    System.out.println("philosopher " + (number + 1) + " grabs left chopstick.");
                    rightchopstick.grab();
                    System.out.println("philosopher " + (number + 1) + " grabs right chopstick.");
                } else {
                    rightchopstick.grab();
                    System.out.println("philosopher " + (number + 1) + " grabs right chopstick.");
                    leftchopstick.grab();
                    System.out.println("philosopher " + (number + 1) + " grabs left chopstick.");
                }
                eat();
                leftchopstick.release();
                System.out.println("philosopher " + (number+1) + " releases left chopstick.");
                rightchopstick.release();
                System.out.println("philosopher " + (number+1) + " releases right chopstick.");
            }
        }

        void eat() {
            try {
                int sleepTime = ThreadLocalRandom.current().nextInt(0, 1000);
                System.out.println("philosopher " + (number+1) + " eats for " + sleepTime);
                Thread.sleep(sleepTime);
            }
            catch (Exception e) {
                e.printStackTrace(System.out);
            }
        }

    }

    public static void main(String argv[]) {

        for (int i = 0; i < philosopher; i++) {
            chopsticks[i] = new Chopstick();
        }

        for (int i = 0; i < philosopher; i++) {
            philosophers[i] = new philosopher(i, chopsticks[i], chopsticks[(i + 1) % philosopher]);
            philosophers[i].start();
        }
    }

}

