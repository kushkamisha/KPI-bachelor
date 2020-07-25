import org.junit.AfterClass;
import org.junit.BeforeClass;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Tests for the List class
 */
public class ListTest {

    private static List<Integer> lstNoParameters;
    private static List<Integer> lstOneParameter;
    private static List<Integer> lstArrayInit;

    @BeforeClass
    public static void init() {
        lstNoParameters = new List<>();
        lstOneParameter = new List<>(5);

        ArrayList<Integer> arr = new ArrayList<>();

        arr.add(1);
        arr.add(-9999);
        arr.add(1034);

        lstArrayInit = new List<>(arr);
    }

    @org.junit.Test
    public void add() {
        lstNoParameters.add(15);
        lstOneParameter.add(15);
        lstArrayInit.add(15);

        lstNoParameters.add(-12);
        lstOneParameter.add(-12);
        lstArrayInit.add(-12);
    }

    @org.junit.Test
    public void get() {
        assertEquals((long)15, (long)lstNoParameters.get(0));
        assertEquals((long)5, (long)lstOneParameter.get(0));
        assertEquals((long)1, (long)lstArrayInit.get(0));

        lstOneParameter.get(15);
        lstOneParameter.get(15);
        lstArrayInit.get(15);
    }

    @org.junit.Test
    public void expand() {
        lstNoParameters.expand();
        lstOneParameter.expand();
        lstArrayInit.expand();
    }

    @org.junit.Test
    public void size() {
        assertEquals(0+2, lstNoParameters.size());
        assertEquals(1+2, lstOneParameter.size());
        assertEquals(3+2, lstArrayInit.size());
    }

    @org.junit.Test
    public void show() {
        lstNoParameters.show();
        lstOneParameter.show();
        lstArrayInit.show();

        List<Integer> lst = new List<>();
        lst.show();
    }

    @org.junit.Test
    public void swap() {
        lstNoParameters.swap(0, 1);
        lstOneParameter.swap(0, 1);

        lstArrayInit.swap(0, 1);
        assertEquals((long)-9999, (long)lstArrayInit.get(0));
    }

    @AfterClass
    public static void after() {
        lstNoParameters = null;
        lstOneParameter = null;
        lstArrayInit = null;
    }
}
