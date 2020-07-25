/**
 * Java labs - Lab5
 * @version 1.5 2018-03-23
 * @author Misha Kushka
 */

/**
 * Main class of the program.
 */
public class Main {

    public static void main(String[] args) {

        // Init game room's object to play with it.
        GameRoom gameRoom = new GameRoom(23, 9);

        gameRoom.playWithToys();

        System.out.println("\n-- SORTED ------------------------------");

        gameRoom.sortToys();
        gameRoom.playWithToys();

        System.out.println();

        int min = 10;
        int max = 13;

        Toy firstToyFromRange = gameRoom.getFirstToyFromPriceRange(min, max);

        if (firstToyFromRange != null) {
            System.out.println("Toy from " + min + " to " + max + " is " + firstToyFromRange.getToyName() + ".");
        } else {
            System.out.println("There is no toys from range (" + min + ", " + max + ")");
        }

    }

}
