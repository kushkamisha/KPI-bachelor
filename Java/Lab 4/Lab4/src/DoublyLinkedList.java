/**
 * Implementation of Doubly linked list
 * to store objects of different types
 */
public class DoublyLinkedList {

    // Subsidiary class to implement Doubly linked list
    private class Node {
        public Object value;
        public Node nextNode;
        public Node prevNode;
    };

    Node firstNode;
    Node lastNode;

    DoublyLinkedList() {
        firstNode = null;
        lastNode = null;
    }

    // Add element to the end of the list
    boolean add(Object value) {
        Node currNode = lastNode;
        lastNode = new Node();
        if (lastNode != null) {
            if(firstNode == null)
                firstNode = lastNode;
            lastNode.value = value;
            lastNode.nextNode = null;
            lastNode.prevNode = currNode;
            if(currNode != null)
                currNode.nextNode = lastNode;
            return true;
        }

        return false;
    }

    // Get size of the list
    int size() {
        int size = 0;
        Node currNode = firstNode;

        while (currNode != null) {
            size++;
            currNode = currNode.nextNode;
        }

        return size;
    }

    // Get i-th element from the list
    Object get(int i) {
        int position = 0;
        Node currNode = firstNode;

        if (i >= this.size()) {
            System.err.println("Too big index. Try smaller one.");
            System.exit(1);
        }

        while (currNode != null) {
            if (position == i) {
                return currNode.value;
            }
            currNode = currNode.nextNode;
            position++;
        }

        return currNode.value;
    }

    // Prints list on the screen
    void print() {
        Node currNode = firstNode;

        while (currNode != null) {
            System.out.println(currNode.value);
            currNode = currNode.nextNode;
        }
    }
}
