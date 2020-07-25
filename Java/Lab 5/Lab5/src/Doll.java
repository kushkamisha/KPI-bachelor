/**
 * Doll toy for girls of different ages.
 */
class Doll extends Toy {

    private int defaultToyPrice = 5; // price of the toy, not considering child age

    /**
     * Call's the constructor of the parent's Toy class,
     * sets toy's price depends of the default toy price
     * and age of the child.
     *
     * @param childAge Age of the child.
     * @param newToyName Name of the toy.
     */
    Doll(int childAge, String newToyName) {
        super(childAge, newToyName);
        setToyPrice(defaultToyPrice * getToySize());
    }

    /**
     * Some another method for this class.
     */
    void dressNewDress() {
        System.out.println("Now your doll wears in the new dress.");
    }

}
