/**
 * Java labs – Lab6
 * @version 1.0 2018-04-03
 * @author Misha Kushka
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
