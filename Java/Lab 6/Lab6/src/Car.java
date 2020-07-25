/**
 * Car toy for boys of different ages.
 */
class Car extends Toy {

    private int defaultToyPrice = 3; // price of the toy, not considering child age

    /**
     * Call's the constructor of the parent's Toy class,
     * sets toy's price depends of the default toy price
     * and age of the child.
     *
     * @param childAge Age of the child.
     * @param newToyName Name of the toy.
     */
    Car(int childAge, String newToyName) {
        super(childAge, newToyName);
        setToyPrice(defaultToyPrice * getToySize());
    }

    /**
     * Some another method for this class.
     */
    void changeTires() {
        System.out.println("Now your car is equiped with the new tires.");
    }

}
