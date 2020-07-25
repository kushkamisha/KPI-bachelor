/**
 * Word, made from letters
 */
class Word {
    DoublyLinkedList letters = new DoublyLinkedList();

    Word(String s) {
        for (char letter : s.toCharArray()) {
            letters.add(new Letter(letter));
        }
    }

    // Returns whole word
    String getWord() {
        String result = "";

        for (int i = 0; i < letters.size(); ++i) {
            result = result + ((Letter)letters.get(i)).getLetter();
        }

        return result;
    }

    // Checks is current string a palindrome
    boolean checkPalindrome(String s) {
        int n = s.length();
        for (int i = 0; i < n / 2; ++i) {
            if (s.charAt(i) != s.charAt(n-i-1))
                return false;
        }

        return true;
    }

    // Get the longest palindrome in the word
    String longestPalindrome() {
        int left = 0;
        final int right = letters.size();
        int j = right;
        String temp = "";
        String theLongest = "";

        while (left < right-1) {
            temp = substring(left, j);
            j -= 1;

            if (this.checkPalindrome(temp) && theLongest.length() < temp.length()) {
                theLongest = temp;
            }

            if (j < left+2) {
                left += 1;
                j = right;
            }
        }

        return theLongest;
    }

    // Get substring from list of Letters objects
    String substring(int a, int b) {
        String result = "";

        for (int i = a; i < b; ++i) {
            result = result + ((Letter)letters.get(i)).getLetter();
        }

        return result;
    }
}
