/**
 * Implementation of the gaming room for children
 * of different ages.
 */
class GameRoom {

    private List<Toy> toys = new List<>(); // array of toys in the game room
    private int childAge; // age of the child
    private int payed; // how much was payed for the room

    /**
     * Allow to pay for playing in the game room.
     * Depending on the amount of money child can
     * play with different number of toys.
     *
     * @param amount Amount of money to pay for playing.
     * @param age Age of the child in the room.
     */
    GameRoom(int amount, int age) {
        // Too low payment checker.
        if (amount < 1) {
            System.err.println("Sorry, but the cheapest toy costs $1.");
            System.exit(1);
        }
        childAge = age;
        payed = amount;

        // Fill toys array with toys.
        giveToys();

        // Show how many toys are available depends of the payed amount.
        try {
            System.out.println("Now you can play with " + toys.size() + " toys.");
        } catch (NullPointerException e) {
            System.err.println("Add elements to the toys array first.");
            System.exit(2);
        }
    }

    /**
     * Fill the toys array with different toys object's
     * depends of the payed amount for the room.
     */
    void giveToys() {

        // Toys, which are in the room.
        List<Toy> defaultToys = new List<>();

        defaultToys.add(new Car(childAge, "super car"));
        defaultToys.add(new Doll(childAge, "cool doll"));
        defaultToys.add(new Ball(childAge, "amazing ball"));
        defaultToys.add(new Cube(childAge, "crazy cube"));

        int[] defaultToyPrices = new int[defaultToys.size()]; // prices of toys in the room

        // Set prices for all toys in the room depending on the child age.
        for (int i = 0; i < defaultToyPrices.length; i++) {
            defaultToyPrices[i] = defaultToys.get(i).getToyPrice();
        }

        int totalPrice = 0; // total price of all toys for the current child
        int iteration = 0; // number of iterations of adding toys

        // A little bit randomly choose toys for the particular child
        // depending on the child age and payed amount.
        while (totalPrice < payed) {
            switch (iteration%4) {
                case 0:
                    if (totalPrice + defaultToyPrices[0] <= payed) {
                        toys = add(toys, defaultToys.get(0));
                        totalPrice += defaultToyPrices[0];
                    }
                    break;
                case 1:
                    if (totalPrice + defaultToyPrices[1] <= payed) {
                        toys = add(toys, defaultToys.get(1));
                        totalPrice += defaultToyPrices[1];
                    }
                    break;
                case 2:
                    if (totalPrice + defaultToyPrices[2] <= payed) {
                        toys = add(toys, defaultToys.get(2));
                        totalPrice += defaultToyPrices[2];
                    }
                    break;
                default:
                    if (totalPrice + defaultToyPrices[3] <= payed) {
                        toys = add(toys, defaultToys.get(3));
                        totalPrice += defaultToyPrices[3];
                    }
                    break;
            }
            iteration++;
        }

        System.out.println("Total price: $" + totalPrice);

    }

    /**
     * Add element to the Toy's array.
     *
     * @param originalArray Array to put element into.
     * @param newItem Element to put.
     * @return New array with added element.
     */
    private static List<Toy> add(List<Toy> originalArray, Toy newItem) {
        int currentSize = originalArray.size();
        int newSize = currentSize + 1;
        List<Toy> tempArray = new List<>();
        for (int i = 0; i < currentSize; i++) {
            tempArray.add(originalArray.get(i));
        }
        tempArray.add(newItem);
        return tempArray;
    }

    /**
     * Execute method of playing with all toys
     * of the particular child.
     */
    void playWithToys() {
        for (int i = 0; i < toys.size(); i++) {
            toys.get(i).playWithToy();
        }
    }

    /**
     * Get first toy from the setted range by toy's price.
     *
     * @param min Minimum price of the toy to find.
     * @param max Maximum price of the toy to find.
     * @return First toy with price from range if found,
     * or null otherwise.
     */
    Toy getFirstToyFromPriceRange(int min, int max) {

        // Check is min < max.
        if (min > max) {
            System.out.println("Attention! min value is bigger, than max value!");
        }

        // Iteratively find toy from the given range.
        for (int i = 0; i < toys.size(); i++) {
            if (toys.get(i).getToyPrice() >= min && toys.get(i).getToyPrice() <= max) {
                return toys.get(i);
            }
        }

        return null;
    }

    /**
     * Sort toys by the name of their classes alphabetically.
     */
    void sortToys() {
        int i, j; // iterators
        int n = toys.size(); // length of the toys array
        Toy temp; // temporary Toy object to swap elements

        // Bubble sort for the array of toys.
        for (i = 0; i < n-1; i++) {
            for (j = 0; j < n - i - 1; j++) {
                if (isBiggerThan(toys.get(j), toys.get(j+1))) {
                    toys.swap(j, j+1);
                }
            }
        }
    }

    boolean isBiggerThan(Toy first, Toy second) {
        int firstIndex, secondIndex;

        // Align class names with indexes.
        // First object.
        switch (first.getClass().getName()) {
            case ("Ball"):
                firstIndex = 0;
                break;
            case ("Car"):
                firstIndex = 1;
                break;
            case ("Cube"):
                firstIndex = 2;
                break;
            default:
                firstIndex = 3;
        }

        // Second object.
        switch (second.getClass().getName()) {
            case ("Ball"):
                secondIndex = 0;
                break;
            case ("Car"):
                secondIndex = 1;
                break;
            case ("Cube"):
                secondIndex = 2;
                break;
            default:
                secondIndex = 3;
        }

        if (firstIndex > secondIndex)
            return true;

        return false;
    }

}
