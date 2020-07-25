/**
 * Ball toy for girls & boys of different ages.
 */
class Ball extends Toy {

    private int defaultToyPrice = 1; // price of the toy, not considering child age

    /**
     * Call's the constructor of the parent's Toy class,
     * sets toy's price, which isn't depends on the age
     * of the child.
     *
     * @param childAge Age of the child.
     * @param newToyName Name of the toy.
     */
    Ball(int childAge, String newToyName) {
        super(childAge, newToyName);
        setToyPrice(defaultToyPrice);
    }

    /**
     * Some another method for this class.
     */
    void inflate() {
        System.out.println("Inflate the ball.");
    }

}
