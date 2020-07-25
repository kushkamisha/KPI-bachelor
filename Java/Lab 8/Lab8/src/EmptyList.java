/**
 * Exception to indicate when list is empty.
 */
public class EmptyList extends Exception {
    private int arraySize; // size of the array

    /**
     * Set size of the array.
     * @param size Size of the array.
     */
    EmptyList(int size) {
        arraySize = size;
    }

    /**
     * Message which says that can't show the array.
     * @return Caution about empty array.
     */
    public String toString() {
        return "The list is empty, can't show it.";
    }
}
