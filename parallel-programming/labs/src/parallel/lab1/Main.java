package parallel.lab1;

import parallel.lab1.utils.MultiThread;
import static parallel.lab1.utils.Matrix.createMatrix;
import static parallel.lab1.utils.Matrix.printMatrix;

public class Main {
    private static int N = 5000;
    private static int[][] mtr = createMatrix(N, N, 9);
    private static int[][] mtr2 = new int[N][N];

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < N; i++)
            mtr2[i] = mtr[i].clone();

//        printMatrix(mtr);

        // Sequential
        long startSeq = System.nanoTime();
        int sum = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                sum += mtr[i][j] + mtr[j][i];
            }
            mtr[i][i] = sum;
            sum = 0;
        }

        System.out.printf("Sequential time: %d ms\n", (System.nanoTime() - startSeq) / 1000000);

//        System.out.println();
//        printMatrix(mtr);
//        System.out.println();
//        printMatrix(mtr2);

        // Parallel
        long startPar = System.nanoTime();
        int NUM_OF_CORES = 8;
        MultiThread[] threads = new MultiThread[N];

        for (int i = 0; i < NUM_OF_CORES; i++) {
            threads[i] = new MultiThread(
                mtr2,
                N / NUM_OF_CORES * i,
                i == NUM_OF_CORES - 1 ?
                    N :
                    N / NUM_OF_CORES * (i + 1)
            );
            threads[i].start();
        }

        for (int i = 0; i < NUM_OF_CORES; i++) {
            threads[i].join();
        }

        int[] result;
        for (int i = 0; i < NUM_OF_CORES; i++) {
            result = threads[i].getResult();
            for (int j = 0; j < N; j++) {
                if (result[j] == 0) continue;
                mtr[j][j] = result[j];
            }
        }

//        System.out.println();
//        printMatrix(mtr2);

        System.out.printf("Parallel time: %d ms", (System.nanoTime() - startPar) / 1000000);
    }
}
