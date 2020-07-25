/**
 * Implementation of the real-world toy with it's
 * properties such as size, type, color and such things
 * to do with it as playing with toy.
 */
class Toy {

    private short toySize; // size of the toy
    private int toyPrice; // price of the toy
    public final String toyName; // name of the toy

    /**
     * Set toy's name and size.
     * @param newToyName Name of the toy.
     * @param newToySize Size of the toy.
     */
    Toy(String newToyName, short newToySize) {
        toySize = newToySize;
        toyName = newToyName;
    }

    /**
     * Toy's constructor, which sets toy's name
     * depending on the child age.
     *
     * @param childAge Age of the child.
     * @param newToyName Part of the toy name without
     * appendix of it's size.
     */
    Toy(int childAge, String newToyName) {
        if (childAge <= 5) {
            toySize = 1;
            newToyName = "small " + newToyName;
        } else if (childAge > 5 && childAge <= 10) {
            toySize = 2;
            newToyName = "medium " + newToyName;
        } else {
            toySize = 3;
            newToyName = "big " + newToyName;
        }

        toyName = newToyName;
    }

    /**
     * Immitates process of playing with toy.
     */
    public void playWithToy() {
        System.out.println("Now child is playing with the " + toyName + ".");
    }

    /**
     * Setter for the toy price.
     * @param newPrice New price of the toy to set.
     */
    public void setToyPrice(int newPrice) {
        toyPrice = newPrice;
    }

    /**
     * Getter for the toy size.
     * @return Size of the toy.
     */
    public short getToySize() {
        return toySize;
    }

    /**
     * Getter for the toy prise.
     * @return Price of the toy.
     */
    public int getToyPrice() {
        return toyPrice;
    }

    /**
     * Getter for the toy name.
     * @return Toy's name.
     */
    public String getToyName() {
        return toyName;
    }

}
