/**
 * Stores and processes the text
 */
public class Text {
    private final String SENTENCE_DELIMITERS = "\\. |\\! |\\? |\\.|\\!|\\?";
    private DoublyLinkedList sentences = new DoublyLinkedList();

    Text(String text) {
        // Check whether the input string is empty
        if (text.length() == 0) {
            System.err.println("Input text is empty");
            System.exit(2);
        }

        String[] stringSentences = getSentencesFromString(text);

        for (String sentence : stringSentences) {
            System.out.println("Sentence: " + sentence);
            sentences.add(new Sentence(sentence));
        }
    }

    // Split string by separators
    String[] getSentencesFromString(String s) {
        s = clearText(s);
        String[] data = s.split(SENTENCE_DELIMITERS);

        return data;
    }

    // Clear the text from tabs and spaces duplicates
    String clearText(String s) {
        s = s.replaceAll("\t", " ");
        s = s.replaceAll(" +", " ");

        return s;
    }

    // Get the longest palindrome in the text
    String longestPalindrome() {
        String theLongest = "";

        for (int i = 0; i < sentences.size(); ++i) {
            if (((Sentence)sentences.get(i)).longestPalindrome().length() > theLongest.length()) {
                theLongest = ((Sentence)sentences.get(i)).longestPalindrome();
            }
        }

        return theLongest;
    }
}
