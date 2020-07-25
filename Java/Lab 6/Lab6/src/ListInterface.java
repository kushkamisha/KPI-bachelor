/**
 * List interface with it's main methods.
 * @param <T> Generic parameter.
 */
public interface ListInterface<T> {

    /**
     * Get array's element by index.
     * @param index Index of searching element.
     * @return Element from array by index.
     */
    public T get(int index);

    /**
     * Expand the array, if it's too small.
     */
    public void expand();

    /**
     * Get current size of the array.
     * @return Size of the array.
     */
    public int size();

    /**
     * Show the array on the screen.
     */
    public void show();

    /**
     * Swap elements in the list.
     * @param i Index of the first element.
     * @param j Index of the second element.
     */
    public void swap(int i, int j);

}
