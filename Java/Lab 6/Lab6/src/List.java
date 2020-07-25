import java.lang.reflect.Array;
import java.util.ArrayList;

/**
 * List implementation with it's main methods.
 * @param <T> Generic parameter.
 */
public class List<T> implements ListInterface<T> {

    private T[] arr; // array to store items in the list
    private int currentSize; // current length of the array
    private int maxSize; // current maximum size of the array
    private Class<T> elementType; // type of elements in the array

    /**
     * List class constructor with one parameter: type of elements.
     */
    public List() {
        maxSize = 15;
        currentSize = 0;
    }

    /**
     * List constructor with 2 parameters: type of elements and one element.
     * @param element Element to add to the list.
     */
    public List(T element) {
        maxSize = 15;
        currentSize = 1;
        elementType = (Class<T>) element.getClass().getSuperclass();
        arr = (T[]) Array.newInstance(elementType, maxSize);
        arr[0] = element;
    }

    /**
     * Add element to the end of the array.
     * @param element Element to push.
     */
    public void add(T element) {
        // Expand array if it's too small
        if (currentSize >= maxSize) {
            expand();
        }

        if (elementType == null) {
            elementType = (Class<T>) element.getClass().getSuperclass();
            arr = (T[]) Array.newInstance(elementType, maxSize);
        }

        arr[currentSize] = element;
        currentSize++;
    }

    /**
     * List constructor with 2 parameters: type of elements and array of elements
     * to put in this structure.
     * @param newArr Array to put to the list.
     */
    public List(ArrayList<T> newArr) {
        maxSize = 15;
        currentSize = newArr.size();

        // Array is not empty
        if (currentSize != 0) {
            elementType = (Class<T>) newArr.get(0).getClass().getSuperclass();

            while (newArr.size() > maxSize) {
                expand();
            }

            arr = (T[]) Array.newInstance(elementType, maxSize);

            for (int i = 0; i < newArr.size(); i++) {
                arr[i] = newArr.get(i);
            }
        }
    }

    /**
     * Get array's element by index.
     * @param index Index of searching element.
     * @return Element from array by index.
     */
    public T get(int index) {
        if (index >= 0 && index < currentSize) {
            return arr[index];
        } else {
            System.err.println("Index is out of range");
        }

        return (T) null;
    }

    /**
     * Expand the array, if it's too small.
     */
    public void expand() {
        int newSize = maxSize + (int)(maxSize * 0.3);
        T[] newArr = (T[]) Array.newInstance(elementType, newSize);

        System.arraycopy( arr, 0, newArr, 0, maxSize);

        maxSize = newSize;
        arr = newArr;
    }

    /**
     * Get current size of the array.
     * @return Size of the array.
     */
    public int size() {
        return currentSize;
    }

    /**
     * Show the array on the screen.
     */
    public void show() {
        for (int i = 0; i < currentSize; i++) {
            System.out.println(arr[i]);
        }
    }

    /**
     * Swap elements in the list.
     * @param i Index of the first element.
     * @param j Index of the second element.
     */
    public void swap(int i, int j) {
        if (i >= 0 && i < currentSize && j >= 0 && j < currentSize) {
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            System.err.println("One or both of indexes are out of range.");
        }
    }

}
