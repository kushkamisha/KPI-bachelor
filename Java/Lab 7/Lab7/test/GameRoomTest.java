import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Tests for the GameRoom class.
 */
public class GameRoomTest {

    private static GameRoom gameRoom;

    @BeforeClass
    public static void init() {
        gameRoom = new GameRoom(28, 12);
    }

    @Test
    public void notEnoughMoney() {
        GameRoom gr = new GameRoom(-5, 5);
    }

    @Test
    public void playWithToys() {
        gameRoom.playWithToys();
    }

    @Test
    public void getFirstToyFromPriceRange() {
        Toy firstToyFromRange = gameRoom.getFirstToyFromPriceRange(5, 13);
        assertEquals("big super car", firstToyFromRange.getToyName());

        Toy firstToyFromRange2 = gameRoom.getFirstToyFromPriceRange(10, 13);
        assertEquals(null, firstToyFromRange2);
    }

    @Test
    public void sortToys() {
        gameRoom.sortToys();
    }

    @Test
    public void isBiggerThan() {
        List<Toy> toys = new List<>();

        toys.add(new Car(5, "super car"));
        toys.add(new Doll(5, "cool doll"));
        toys.add(new Ball(5, "amazing ball"));
        toys.add(new Cube(5, "crazy cube"));

        assertEquals(true, gameRoom.isBiggerThan(toys.get(1), toys.get(0)));
        assertEquals(true, gameRoom.isBiggerThan(toys.get(1), toys.get(2)));
        assertEquals(true, gameRoom.isBiggerThan(toys.get(3), toys.get(2)));
    }

    @AfterClass
    public static void after() {
        gameRoom = null;
    }

}
