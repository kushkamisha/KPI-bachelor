/**
 * Java labs - Lab4
 * @version 1.2 2018-03-10
 * @author Misha Kushka
 */

public class Main {

    public static void main(String[] args) {

        String s = "abba, cool sool;helloljleh.      What?          Blue space!bcb?";
        Text text = new Text(s);
        String theLongest = text.longestPalindrome();

        System.out.println("The longest palindrome: " + theLongest);

    }
}
