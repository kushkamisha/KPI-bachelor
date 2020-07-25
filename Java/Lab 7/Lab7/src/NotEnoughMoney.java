/**
 * Exception to indicate when there are not enough money to visit the game room.
 */
public class NotEnoughMoney extends Exception {

    private int amountOfMoney; // amount of money for the room

    /**
     * Sets amount of money for the game room.
     * @param amount Amount of money.
     */
    NotEnoughMoney(int amount) {
        amountOfMoney = amount;
    }

    /**
     * Caution, which tells why exception runs.
     * @return Caution about too small amount of money.
     */
    public String toString() {
        return "Sorry, but $" + amountOfMoney + " is not enough to visit the game room.";
    }
}
