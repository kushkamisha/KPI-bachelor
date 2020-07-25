package parallel.lab1.utils;
import java.util.Random;

public class Matrix {

    /**
     * Generate an nxm random filled matrix
     * @param n - Number of rows
     * @param m - Number of columns
     * @param max - Maximum value in the matrix
     * @return Generated nxm matrix
     */
    public static int[][] createMatrix(int n, int m, int max) {
        Random rand = new Random();
        int[][] mtr = new int[n][m];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                mtr[i][j] = rand.nextInt(max+1);

        return mtr;
    }

    public static void printMatrix(int[][] mtr) {
        for (int[] row : mtr) {
            for (int cell : row)
                System.out.printf("%4d", cell);
            System.out.println();
        }
    }

    /**
     * Multiply two matrices
     * @param mtr1
     * @param mtr2
     * @return
     */
    public static int[][] multiplyMatrices(int[][] mtr1, int[][] mtr2) {
        int[][] result = new int[mtr1.length][mtr2[0].length];
        int buffer = 0;

        for (int i = 0; i < mtr1.length; i++) {
            for (int j = 0; j < mtr2[0].length; j++) {
                for (int k = 0; k < mtr2.length; k++)
                    buffer += mtr1[i][k] * mtr2[k][j];
                result[i][j] = buffer;
                buffer = 0;
            }
        }

        return result;
    }

}
