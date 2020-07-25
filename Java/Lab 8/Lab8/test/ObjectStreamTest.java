import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ObjectStreamTest {

    private static ObjectStream stream;

    /**
     * Create 2 objects and 2 files to work with.
     */
    @BeforeAll
    public static void createFiles() {
        stream = new ObjectStream("data/output");

        // Objects list

        ArrayList<Toy> toys = new ArrayList<>();
        toys.add(new Car("cool carssss", (short)2));
        toys.add(new Cube("amazing cube", (short)2));
        toys.add(new Doll("puper baller", (short)3));
        toys.add(new Ball("amazing ball", (short)1));

        List<Toy> objLst = new List<>(toys);

        ObjectStream strbin = new ObjectStream("data/output");
        strbin.saveListToFile(objLst, "binary");

        ObjectStream strjson = new ObjectStream("data/output");
        strbin.saveListToFile(objLst, "json");
    }

    /**
     * Get list from JSON file.
     */
    @Test
    public void getListFromJSONFile() {
        stream.getListFromFile("json");
    }

    /**
     * Get list from binary file.
     */
    @Test
    public void getListFromBinaryFile() {
        stream.getListFromFile("binary");
    }

    /**
     * Get String type list from binary file.
     */
    @Test
    public void getStringListFromBinaryFile() {
        ObjectStream bin = new ObjectStream("data/output");
        bin.getListFromFile("binary");
    }

    /**
     * Get integer type list from binary file.
     */
    @Test
    public void getIntListFromBinaryFile() {
        ObjectStream bin = new ObjectStream("data/output");
        bin.getListFromFile("binary");
    }

    /**
     * Get Toy class list from binary file.
     */
    @Test
    public void getObjectListFromBinaryFile() {
        ObjectStream bin = new ObjectStream("data/output");;
        bin.getListFromFile("binary");
    }

    /**
     * Get Toy class list from JSON file.
     */
    @Test
    public void getObjectListFromJSONFile() {
        ObjectStream bin = new ObjectStream("data/output");
        bin.getListFromFile("binary");
    }

    /**
     * Save string type list to binary file.
     */
    @Test
    public void saveStringListToBinaryFile() {
        // String list
        List<String> lst = new List<>();

        lst.add("Owh");
        lst.add("yey");
        lst.add("HaLoEmMeTnn");
        lst.add("");
        lst.add("Yellow submarine!");

        ObjectStream bin = new ObjectStream("data/output");
        bin.saveListToFile(lst, "binary");
    }

    /**
     * Save integer list to binary file.
     */
    @Test
    public void saveIntListToBinaryFile() {
        // Integer list
        List<Integer> intLst = new List<>();

        intLst.add(15);
        intLst.add(101);
        intLst.add(-12345678);
        intLst.add(257);
        intLst.add(0);

        ObjectStream bin = new ObjectStream("data/output");
        bin.saveListToFile(intLst, "binary");
    }

    /**
     * Save Toy class list to binary file.
     */
    @Test
    public void saveObjectListToBinaryFile() {
        // Toy list
        ArrayList<Toy> toys = new ArrayList<>();
        toys.add(new Car("cool carssss", (short)2));
        toys.add(new Cube("amazing cube", (short)2));
        toys.add(new Doll("puper baller", (short)3));
        toys.add(new Ball("amazing ball", (short)1));

        List<Toy> objLst = new List<>(toys);

        ObjectStream bin = new ObjectStream("data/output");
        bin.saveListToFile(objLst, "binary");
    }

    /**
     * Save Toy class list to JSON file.
     */
    @Test
    public void saveObjectListToJSONFile() {
        // Toy list
        ArrayList<Toy> toys = new ArrayList<>();
        toys.add(new Car("cool carssss", (short)2));
        toys.add(new Cube("amazing cube", (short)2));
        toys.add(new Doll("puper baller", (short)3));
        toys.add(new Ball("amazing ball", (short)1));

        List<Toy> objLst = new List<>(toys);

        ObjectStream json = new ObjectStream("data/output");
        json.saveListToFile(objLst, "json");
    }

    /**
     * Check whether string is numeric.
     */
    @Test
    public void isNumeric() {
        assertEquals(true, stream.isNumeric("10"));
        assertEquals(true, stream.isNumeric("34.2"));
        assertEquals(true, stream.isNumeric("0"));
    }

    /**
     * Check whether string is not numeric.
     */
    @Test
    public void isNotNumeric() {
        assertEquals(false, stream.isNumeric("hy"));
        assertEquals(false, stream.isNumeric("10s"));
        assertEquals(false, stream.isNumeric(""));
    }

    /**
     * Get bytes array from binary file.
     */
    @Test
    public void getBytesFromFile() {
        stream.getBytesFromFile();
    }

    /**
     * Convert bytes array (with saved integers) to the integer array.
     */
    @Test
    public void bytesArrayToIntArray() {
        byte[] bytes = {
                0, 0, 0, 15, // 15
                0, 0, 0, 101, // 101
                -1, 67, -98, -78, // -12345678
                0, 0, 1, 1, // 257
                0, 0, 0, 0 // 0
        };
        ArrayList<Integer> arr;
        Integer[] checkArray = {15, 101, -12345678, 257, 0};

        arr = stream.bytesArrayToIntArray(bytes);

        for (int i = 0; i < arr.size(); i++) {
            assertEquals(checkArray[i], arr.get(i));
        }
    }

    /**
     * Create Toy class object from the string data.
     */
    @Test
    public void makeObjectListFromStringArray() {
        ArrayList<String> arr = new ArrayList<>() {{
            add("Car");
            add("pretty car");
            add("2");
        }};

        stream.makeObjectListFromStringArray(arr);
    }

    /**
     * Add arrays of keys and values to the JSON file.
     */
    @Test
    public void addToJSON() {
        ArrayList<String> keys = new ArrayList<>() {{
            add("class");
            add("name");
            add("size");
        }};
        ArrayList<String> objects = new ArrayList<>();

        ArrayList<String> values = new ArrayList<>() {{
            add("Car");
            add("pretty car");
            add("2");
        }};

        stream.addToJSON(keys, objects);
    }

    /**
     * Clean all additional symbols from JSON file.
     */
    @Test
    public void cleanJSON() {
        String data = "[\n" +
                "\t{\n" +
                "\t\t\"class\": \"Car\",\n" +
                "\t\t\"name\": \"cool carssss\",\n" +
                "\t\t\"size\": 2\n" +
                "\t},\n" +
                "\t{\n" +
                "\t\t\"class\": \"Cube\",\n" +
                "\t\t\"name\": \"amazing cube\",\n" +
                "\t\t\"size\": 2\n" +
                "\t},\n" +
                "\t{\n" +
                "\t\t\"class\": \"Doll\",\n" +
                "\t\t\"name\": \"puper baller\",\n" +
                "\t\t\"size\": 3\n" +
                "\t},\n" +
                "\t{\n" +
                "\t\t\"class\": \"Ball\",\n" +
                "\t\t\"name\": \"amazing ball\",\n" +
                "\t\t\"size\": 1\n" +
                "\t}\n" +
                "]";

        assertEquals("Carcool carssss2Cubeamazing cube2Dollpuper baller3Ballamazing ball1", stream.cleanJSON(data));
    }

}
