import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {

        // String list

        List<String> lst = new List<>();

        lst.add("Owh");
        lst.add("yey");
        lst.add("HaLoEmMeTnn");
        lst.add("");
        lst.add("Yellow submarine!");

        // Integer list

        List<Integer> intLst = new List<>();

        intLst.add(15);
        intLst.add(101);
        intLst.add(-12345678);
        intLst.add(257);
        intLst.add(0);

        // Objects list

        ArrayList<Toy> toys = new ArrayList<>();
        toys.add(new Car("cool carssss", (short)2));
        toys.add(new Cube("amazing cube", (short)2));
        toys.add(new Doll("puper baller", (short)3));
        toys.add(new Ball("amazing ball", (short)1));

        List<Toy> objLst = new List<>(toys);


        // Write to the file.
        ObjectStream stream = new ObjectStream("data/output");

        // Save list to the file.
        stream.saveListToFile(objLst, "binary"); // lst, intLst, objLst

        // Read from the file.
        List<?> lstFromFile;
        lstFromFile = stream.getListFromFile("binary");

        // Check list.
        lstFromFile.show();
        System.out.println("\nSize: " + lstFromFile.size());



    }

}
