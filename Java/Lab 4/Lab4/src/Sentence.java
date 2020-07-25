/**
 * Sentence with words and separators
 */
class Sentence {
    private final char[] SEPARATORS = {',', ';', '-'};
    private DoublyLinkedList wordsAndSeparators = new DoublyLinkedList();

    // Put all words in the Word class and all separators in the Separator class
    Sentence(String s) {
        String tempWord = "";

        for (char symbol : s.toCharArray()) {
            if (contains(SEPARATORS, symbol)) {
                wordsAndSeparators.add(new Separator(symbol));
                if (tempWord.length() != 0) {
                    wordsAndSeparators.add(new Word(tempWord));
                    tempWord = "";
                }
            } else {
                tempWord = tempWord + symbol;
            }
        }

        if (tempWord.length() != 0) {
            wordsAndSeparators.add(new Word(tempWord));
        }
    }

    // Get the longest palindrome in the sentence
    String longestPalindrome() {
        String theLongest = "";

        for (int i = 0; i < wordsAndSeparators.size(); ++i) {
            if (wordsAndSeparators.get(i).getClass().equals(Word.class)) {
                Word temp = (Word)wordsAndSeparators.get(i);
                if (temp.longestPalindrome().length() > theLongest.length()) {
                    theLongest = temp.longestPalindrome();
                }
            }
        }

        return theLongest;
    }

    // Check is array contains an element
    boolean contains(char[] arr, char element) {
        for (char a : arr) {
            if (a == element)
                return true;
        }

        return false;
    }
}
