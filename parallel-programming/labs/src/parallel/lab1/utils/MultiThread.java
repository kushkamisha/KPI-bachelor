package parallel.lab1.utils;

public class MultiThread extends Thread {
    int[][] mtr;
    int pos;
    int[] result;
    int startIndex;
    int endIndex;

    public MultiThread(int[][] mtr, int startIndex, int endIndex) {
        this.mtr = mtr;
        this.startIndex = startIndex;
        this.endIndex = endIndex;
        this.result = new int[mtr.length];
    }

    public int[] getResult() {
        return result;
    }

    @Override
    public void run() {
        for (int pos = startIndex; pos < endIndex; pos++) {
            for (int i = 0; i < mtr.length; i++) {
                if (i == this.pos) continue;
                result[pos] += mtr[pos][i] + mtr[i][pos];
            }
        }
    }
}
