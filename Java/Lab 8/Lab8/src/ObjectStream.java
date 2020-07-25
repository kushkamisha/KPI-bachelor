import java.io.*;
import java.nio.ByteBuffer;
import java.util.ArrayList;

public class ObjectStream {

    private static String fileName; // name of the saved file

    /**
     * Set filename in the class.
     * @param file Name of the file.
     */
    ObjectStream(String file) {
        fileName = file;
    }


    /**************************
     * Read from the file zone *
     **************************/

    /**
     * Get list from the file.
     * @return Any type List.
     */
    public List<?> getListFromFile(String type) {

        // What file must read.
        if (!(fileName.contains(".json") || fileName.contains(".bin"))) {
            switch (type) {
                case "binary":
                    fileName = fileName + ".bin";
                    break;
                case "json":
                    fileName = fileName + ".json";
                    break;
                default:
                    System.err.println("Unrecognized file type: " + type);
                    System.exit(1);
            }
        }

        // Get bytes array from file.
        byte[] bytes = getBytesFromFile();
        List<?> lst = new List<>();

        if (fileName.contains(".json")) {
            // Read Toy's list from JSON file.
            lst = getObjectListFromJSON();
        } else {
            if (((char) bytes[0]) == 'S') {
                // String list
                lst = getStringListFromFile();

            } else if (((char) bytes[0]) == 'I') {
                // Integer list
                lst = getIntListFromFile();

            } else if (((char) bytes[0]) == 'O') {
                // Objects list
                lst = getObjectListFromFile();

            }
        }

        return lst;
    }

    /**
     * Get string list from the file.
     * @return String list.
     */
    public List<?> getStringListFromFile() {

        // Get bytes array from file.
        byte[] bytes = getBytesFromFile();

        List<Object> lst = new List<>();
        int lengthCounter = 0;
        final int BYTES_LENGTH = 3;

        int bytesCounter = BYTES_LENGTH;
        String element = null;
        byte[] temp = new byte[4];

        for (int i = 1; i < bytes.length; i++) {
            if (lengthCounter == 0) {
                if (bytesCounter == 0) {

                    temp[0] = bytes[i-3];
                    temp[1] = bytes[i-2];
                    temp[2] = bytes[i-1];
                    temp[3] = bytes[i];

                    lengthCounter = bytesArrayToIntArray(temp).get(0);
                    bytesCounter = BYTES_LENGTH;

                    // Show word
                    if (element != null) {
                        lst.add(element);
                    }
                    element = "";
                } else {
                    bytesCounter--;
                }
            } else {
                element = element + (char)bytes[i];
                lengthCounter--;
            }
        }

        lst.add(element);

        return lst;
    }

    /**
     * Get integer list from the file.
     * @return Integer list.
     */
    public List<?> getIntListFromFile() {

        // Get bytes array from file.
        byte[] bytes = getBytesFromFile();

        List<Object> lst = new List<>();
        ArrayList<Integer> arr;
        byte[] withoutIdBytes = new byte[bytes.length-1];

        for (int i = 0; i < withoutIdBytes.length; i++) {
            withoutIdBytes[i] = bytes[i+1];
        }

        arr = bytesArrayToIntArray(withoutIdBytes);

        for (int element : arr) {
            lst.add(element);
        }

        return lst;
    }

    /**
     * Get Toy class list from the file.
     * @return Toy class list.
     */
    public List<?> getObjectListFromFile() {

        // Get bytes array from file.
        byte[] bytes = getBytesFromFile();

        List<?> lst;
        int lengthCounter = 0;
        final int BYTES_LENGTH = 3;

        int bytesCounter = BYTES_LENGTH;
        String element = null;
        byte[] temp = new byte[4];

        ArrayList<String> result = new ArrayList<>();

        // Get string parameters from the file.
        for (int i = 1; i < bytes.length; i++) {
            if (lengthCounter == 0) {
                if (bytesCounter == 0) {

                    temp[0] = bytes[i - 3];
                    temp[1] = bytes[i - 2];
                    temp[2] = bytes[i - 1];
                    temp[3] = bytes[i];

                    lengthCounter = bytesArrayToIntArray(temp).get(0);
                    bytesCounter = BYTES_LENGTH;

                    // Add string to the array
                    if (element != null) {
                        result.add(element);
                    }
                    element = "";
                } else {
                    bytesCounter--;
                }
            } else {
                element = element + (char) bytes[i];
                lengthCounter--;
            }
        }

        result.add(element);

        // Make objects from parameters.
        lst = makeObjectListFromStringArray(result);

        return lst;
    }

    /**
     * Get Toy class list from JSON file.
     * @return Toy's list.
     */
    public List<?> getObjectListFromJSON() {

        BufferedReader reader;
        ArrayList<String> arr = new ArrayList<>();
        List<?> lst;

        try {
            // Read the JSON file.
            reader = new BufferedReader(new FileReader(fileName));
            String line = reader.readLine();

            while (line != null) {

                line = cleanJSON(line);

                if (line.length() != 0) {
                    arr.add(line);
                }
                // Read next line.
                line = reader.readLine();
            }
            reader.close();

        } catch(FileNotFoundException e) {
            System.err.println("No file " + fileName + " in the directory.");
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Input/output error.");
            System.exit(1);
        }

        // Make Toy's list from string array.
        lst = makeObjectListFromStringArray(arr);

        return lst;
    }


    /**************************
     * Write to the file zone *
     *************************/

    /**
     * Save any type list to the file.
     * @param lst List to be saved.
     */
    public void saveListToFile(List<?> lst, String type) {
        if (lst.size() > 0) {

            switch(type) {
                case "binary":
                    fileName = fileName + ".bin";

                    if (lst.get(0) instanceof String) {
                        // String list
                        saveStringListToFile(lst);

                    } else if (lst.get(0) instanceof Integer) {
                        // Integer list
                        saveIntListToFile(lst);

                    } else if (lst.get(0) instanceof Object) {
                        // Object list
                        saveObjectListToFile(lst);

                    }
                    break;

                case "json":
                    fileName = fileName + ".json";

                    saveObjectListToJSON(lst);
                    break;

                default:
                    System.err.println("Sorry, but " + type + " type of file is not supported.");
            }
        } else {
            System.err.println("Sorry, you can't save an empty list.");
        }

    }

    /**
     * Save string list to the file.
     * @param lst String type list.
     */
    public void saveStringListToFile(List<?> lst) {
        try {
            FileOutputStream fs = new FileOutputStream(fileName);

            fs.write('S'); // string type of elements in the file

            byte[] bytes;
            int len;

            for (int i = 0; i < lst.size(); i++) {
                len = lst.get(i).toString().length();
                bytes = lst.get(i).toString().getBytes();

                fs.write(ByteBuffer.allocate(4).putInt(len).array());
                fs.write(bytes);
            }

            fs.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * Save integer type list to the file.
     * @param lst Integer list.
     */
    public void saveIntListToFile(List<?> lst) {

        try {
            FileOutputStream fs = new FileOutputStream(fileName);

            fs.write('I'); // integer type of elements in the file
            byte[] number;

            for (int i = 0; i < lst.size(); i++) {
                number = ByteBuffer.allocate(4).putInt((Integer)lst.get(i)).array();
                fs.write(number);
            }

            fs.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * Save Toy type list to the file.
     * @param lst Toy type list.
     */
    public void saveObjectListToFile(List<?> lst) {

        ArrayList<String> objects = new ArrayList<>();

        for (int i = 0; i < lst.size(); i++) {
            objects.add(lst.get(i).getClass().toString().substring(6));
            objects.add(((Toy)lst.get(i)).getToyName());
            objects.add(Integer.toString(((Toy)lst.get(i)).getToySize()));
        }

        try {
            FileOutputStream fs = new FileOutputStream(fileName);

            fs.write('O'); // Toy (Object) type of elements in the file

            byte[] bytes;
            int len;

            for (int i = 0; i < objects.size(); i++) {
                len = objects.get(i).length();
                bytes = objects.get(i).getBytes();

                fs.write(ByteBuffer.allocate(4).putInt(len).array());
                fs.write(bytes);
            }

            fs.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Save Toy's list to the JSON file.
     * @param lst Toy's list.
     */
    public void saveObjectListToJSON(List<?> lst) {

        ArrayList<String> keys = new ArrayList<>() {{
            add("class");
            add("name");
            add("size");
        }};
        ArrayList<String> objects = new ArrayList<>();

        try {
            for (int i = 0; i < lst.size(); i++) {
                objects.add(lst.get(i).getClass().toString().substring(6));
                objects.add(((Toy) lst.get(i)).getToyName());
                objects.add(Integer.toString(((Toy) lst.get(i)).getToySize()));
            }
        } catch (java.lang.ClassCastException e) {
            System.err.println("Only Toy class and it's child classes supported.");
        }

        // Add new records to the JSON file.
        addToJSON(keys, objects);
    }


    /*****************************
     * Additional functions zone *
     ****************************/

    /**
     * Check whether the string is a number.
     * @param str String to check.
     * @return Is number or not (T/F).
     */
    public static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
        }
        catch(NumberFormatException nfe)
        {
            return false;
        }
        return true;
    }

    /**
     * Get bytes array from file.
     * @return Bytes array.
     */
    public byte[] getBytesFromFile() {
        byte[] getBytes = {};

        try {
            File file = new File(fileName);
            getBytes = new byte[(int) file.length()];
            FileInputStream is = new FileInputStream(fileName);
            is.read(getBytes);
            is.close();
        } catch (FileNotFoundException e) {
            System.err.println("No file " + fileName + " in the directory.");
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Input/output error.");
            System.exit(1);
        }

        return getBytes;
    }

    /**
     * Convert bytes array to an int array.
     * @param bytes Bytes array.
     * @return Integer array.
     */
    public ArrayList<Integer> bytesArrayToIntArray(byte[] bytes) {

        int number = 0;
        int bit;
        ArrayList<Integer> arr = new ArrayList<>();

        for (int i = 0; i < bytes.length; i++) {
            switch (i % 4) {
                case 0:
                    if (bytes[i] >= 0) {
                        bit = bytes[i];
                    } else {
                        bit = 256 + bytes[i];
                    }
                    number += bit * 256 * 256 * 256;
                    break;
                case 1:
                    if (bytes[i] >= 0) {
                        bit = bytes[i];
                    } else {
                        bit = 256 + bytes[i];
                    }
                    number += bit * 256 * 256;
                    break;
                case 2:
                    if (bytes[i] >= 0) {
                        bit = bytes[i];
                    } else {
                        bit = 256 + bytes[i];
                    }
                    number += bit * 256;
                    break;
                default:
                    if (bytes[i] >= 0) {
                        bit = bytes[i];
                    } else {
                        bit = 256 + bytes[i];
                    }
                    number += bit;
                    arr.add(number);
                    number = 0;
                    break;
            }
        }

        return arr;
    }

    /**
     * Make Toy's list from string array.
     * @param arr Input string array.
     * @return Toy's list.
     */
    public List<?> makeObjectListFromStringArray(ArrayList<String> arr) {

        List<Object> lst = new List<>();
        String objType = "";
        String toyName = "";
        short toySize;

        for (int i = 0; i < arr.size(); i++) {
            switch (i % 3) {
                case 0:
                    objType = arr.get(i);
                    break;
                case 1:
                    toyName = arr.get(i);
                    break;
                default:
                    toySize = Short.parseShort(arr.get(i));

                    switch (objType) {
                        case "Car":
                            lst.add(new Car(toyName, toySize));
                            break;
                        case "Cube":
                            lst.add(new Cube(toyName, toySize));
                            break;
                        case "Doll":
                            lst.add(new Doll(toyName, toySize));
                            break;
                        default:
                            lst.add(new Ball(toyName, toySize));
                            break;
                    }

                    break;
            }
        }

        return lst;

    }

    /**
     * Add new key - value records to the JSON file.
     * @param keys String array of keys.
     * @param values String array of values.
     */
    public void addToJSON(ArrayList<String> keys, ArrayList<String> values) {
        try {

            if (values.size() > 0) {
                BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));

                // Write open of the file square bracket.
                writer.write("[");

                String key;
                String value;

                for (int i = 0; i < values.size(); i++) {

                    // New block.
                    if (i % 3 == 0) {
                        writer.write("\n\t{\n\t\t");
                    }

                    // Key, value to add.
                    key = keys.get(i % 3);
                    value = values.get(i);

                    // If value is not number add quotes.
                    if (!isNumeric(value)) {
                        value = "\"" + value + "\"";
                    }

                    // If not the last recording in the block add comma.
                    if (i % 3 != 2) {
                        value = value + ",\n\t\t";
                    }

                    // Write key and value.
                    writer.write("\"" + key + "\": " + value);

                    // If end of the block add closing brace.
                    if (i % 3 == 2) {
                        writer.write("\n\t}");

                        // If not the last block add comma.
                        if (i != values.size()-1) {
                            writer.write(",");
                        }

                    }
                }

            // Write end of the file square bracket.
            writer.write("\n]");

            writer.close();

        } else{
            System.out.println("Can't store an empty list.");
        }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Replace all additional symbols from the JSON text.
     * @param text Text to cleanup.
     * @return Clear text.
     */
    public static String cleanJSON(String text) {
        
        text = text.replace("[", "");
        text = text.replace("{", "");
        text = text.replace("]", "");
        text = text.replace("},", "");
        text = text.replace("}", "");

        text = text.replace("\n", "");
        text = text.replace("\t", "");
        text = text.replace(": ", "");

        text = text.replace("\"class\"", "");
        text = text.replace("\"name\"", "");
        text = text.replace("\"size\"", "");

        text = text.replace("\",", "");
        text = text.replace("\"", "");

        return text;
    }

}
