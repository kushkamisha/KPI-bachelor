import java.util.Scanner;

public class First {
    public static void main(String[] args) {
    		int n = 0;
        Scanner scanner = new Scanner(System.in);
        
        // Read n
        while (true) {
	        System.out.print("Enter n: ");
	        
	        try {
        		n = Integer.parseInt(scanner.nextLine());
        		break;
	        } catch (NumberFormatException e) {
        		System.out.println("n must be an int number");
	        }
        }
        
        System.out.println("Your n now is equal to " + n);
    }
}
