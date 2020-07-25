package parallel.lab3;

/**
 * 1) Розробити програму, яка за допомогою AtomicInteger і метода compareAndSet: виконує наступні
 * операції для одновимірного массиву. Для потоків використовувати ExecutorService або
 * parallelStream.
 * 
 * 2) Створити паралельні фкнкції для знаходження:
 * - кількості елементів за умовою;
 * - мінімального та максимального елементів з індексами;
 * - контрольної суми із використанням XOR.
 */
import java.util.Arrays;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.IntStream;

public class Main {

    private static int numOfElemsEqual(int[] arr, int number) {
        AtomicInteger atomicAccumulator = new AtomicInteger();
        IntStream.of(arr).parallel().forEach(x -> {
            if (x != number) return;

            int oldValue;
            int newValue;
            do {
                oldValue = atomicAccumulator.get();
                newValue = oldValue + 1;
            } while (!atomicAccumulator.compareAndSet(oldValue, newValue));
        });

        return atomicAccumulator.get();
    }

    private static int[][] minAndMaxElemsInArray(int[] arr) {
        AtomicInteger atomicMin = new AtomicInteger(99999);
        AtomicInteger atomicMax = new AtomicInteger(-99999);
        AtomicInteger atomicMinIndex = new AtomicInteger();
        AtomicInteger atomicMaxIndex = new AtomicInteger();

        IntStream.range(0, arr.length).parallel().forEach(i -> {
            int oldMin;
            int newMin;
            int oldMax;
            int newMax;
            int oldMinIndex;
            int newMinIndex;
            int oldMaxIndex;
            int newMaxIndex;

            do {
                oldMin = atomicMin.get();
                oldMax = atomicMax.get();
                oldMinIndex = atomicMinIndex.get();
                oldMaxIndex = atomicMaxIndex.get();

                newMin = arr[i] < oldMin ? arr[i] : oldMin;
                newMax = arr[i] > oldMax ? arr[i] : oldMax;
                newMinIndex = arr[i] < oldMin ? i : oldMinIndex;
                newMaxIndex = arr[i] > oldMax ? i : oldMaxIndex;

            } while (!atomicMin.compareAndSet(oldMin, newMin) ||
                    !atomicMax.compareAndSet(oldMax, newMax) ||
                    !atomicMinIndex.compareAndSet(oldMinIndex, newMinIndex) ||
                    !atomicMaxIndex.compareAndSet(oldMaxIndex, newMaxIndex));
        });

        return new int[][]{
                { atomicMinIndex.get(), atomicMin.get() },
                { atomicMaxIndex.get(), atomicMax.get() }
        };
    }

    private static int calcChecksum(int[] arr) {
        AtomicInteger atomicChecksum = new AtomicInteger();
        IntStream.of(arr).parallel().forEach(x -> {
            int oldValue;
            int newValue;
            do {
                oldValue = atomicChecksum.get();
                newValue = oldValue ^ x;
            } while (!atomicChecksum.compareAndSet(oldValue, newValue));
        });

        return atomicChecksum.get();
    }

    private static void fillArray(int[] arr) {
        for (int i = 0; i < arr.length; i++)
            arr[i] = (int) (Math.random() * 100);
    }

    public static void main(String[] args) {
        int arr[] = new int [1000000];
        fillArray(arr);
//        System.out.println(Arrays.toString(arr));

        int desired = 1;
        System.out.printf("Number of elements equal %d is %d\n\n", desired, numOfElemsEqual(arr, desired));

        System.out.printf("The minimum value in the array is %d on position %d\n",
                minAndMaxElemsInArray(arr)[0][1], minAndMaxElemsInArray(arr)[0][0]);
        System.out.printf("The maximum value in the array is %d on position %d\n\n",
                minAndMaxElemsInArray(arr)[1][1], minAndMaxElemsInArray(arr)[1][0]);

        System.out.println("Checksum of the array is " + calcChecksum(arr));
    }
}
