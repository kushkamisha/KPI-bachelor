import com.sun.net.httpserver.Authenticator;
import org.junit.jupiter.api.Test;

import javax.xml.transform.Result;

import static org.junit.jupiter.api.Assertions.assertEquals;

class Simple {
	private int one;
	private int two;

	Simple() {

    }

	Simple(int a, int b) {
	    one = a;
	    two = b;
    }

    public int multiply(int a, int b) {
	    return a * b;
    }
}

class MyTests {

    @Test
    public void multiplicationOfZeroIntegersShouldReturnZero() {
        Simple simple = new Simple();

        // assert statements
        assertEquals(0, simple.multiply(10, 0), "10 x 0 must be 0");
        assertEquals(0, simple.multiply(0, 10), "0 x 10 must be 0");
        assertEquals(0, simple.multiply(0, 0), "0 x 0 must be 0");
    }
}

public class Main {

	public static void main(String[] args) {



	}

}
