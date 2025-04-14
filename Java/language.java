import java.util.Objects;
import java.util.Scanner;
import java.util.Random;


public class language {
    // Imported random for the random exponent values
    static Random rand = new Random();

    public static void main(String[] args) {
        // Main function calls
        String alpha = getUI("Enter an alphabet like this (abc): ");
        char[] alphabet = parseAlphabet(alpha);
        String[][] language = parseLanguage(alphabet);
        int length = checkLength(language);
        String[] legalStrings = generateValidatedStrings(language, length);
        validateCombinations(legalStrings, language, length);
    }

    // Function that parses the user input for the alphabet together
    public static char[] parseAlphabet(String input) {
        char[] aphla = new char[input.length()];
        for (int i = 0; i < input.length(); i++) {
            aphla[i] = input.charAt(i);
        }
        return aphla;
    }

    // Function just to get user input so you don't have to repeat
    public static String getUI(String prompt) {
        Scanner keyboard = new Scanner(System.in);
        System.out.print(prompt);
        return keyboard.nextLine();
    }

    // Variable checking function that checks if the exponent is a variable or a constant
    public static String[] variableCheckerFunction() {
        String[] variableChecker = new String[26];
        for (int i = 0; i < 26; i++) {
            variableChecker[i] = String.valueOf((char) ('a' + i));
        }
        return variableChecker;
    }

    // Length checking function to check how many total constant exponents there are
    public static int checkLength(String[][] language) {
        int length = 0;
        int counter = 0;
        for (int i = 0; i < language.length; i++) {
            if (language[counter][1] == null) {
                return length;
            }
            length++;
            counter++;
        }
        return length;
    }


    // Function that generates all 20 validated strings.
    public static String[] generateValidatedStrings(String[][] language, int length) {
        // Variables
        String[] legalStrings = new String[20];
        String[] temporaryStrings = new String[20];
        String[] endingString = new String[1];
        String[] variableList = new String[length];
        String[] variableChecker = variableCheckerFunction();
        boolean variableBoolean = false;
        int counter = 0;

        // Adds the variables to the list variableList
        while (language[counter][1] != null) {
            variableList[counter] = language[counter][1];
            counter++;
        }

        // Repeats the alphabet's constants if they have a variable that is a number
        counter = 0;
        while (counter < variableList.length) {
            for (int i = 0; i < 26; i++) {
                if (variableList[counter].contains(variableChecker[i])) {
                    variableBoolean = true;
                }
            }
            if (variableBoolean == false) {
                temporaryStrings[counter] = language[counter][0].repeat(Integer.parseInt(variableList[counter]));
            } else {
                variableBoolean = false;
            }
            counter++;
        }

        // Saves the length of the language before any variable exponents
        legalStrings[0] = temporaryStrings[0];


        // Creates the 20 legal strings for the language while fixing the null differences with the variableList length
        while (counter < 20 + variableList.length) {
            legalStrings[counter - variableList.length] = temporaryStrings[0];
            for (int i = 1; i < variableList.length; i++) {
                if (temporaryStrings[i] != null) {
                    legalStrings[counter - variableList.length] = legalStrings[counter - variableList.length] + temporaryStrings[i];
                } else {
                    legalStrings[counter - variableList.length] = legalStrings[counter - variableList.length] + language[i][0].repeat(rand.nextInt(50));
                }
            }
            counter++;
        }

        // Extraordinary case in case user does a^m or just a exponential variable at the start
        if (temporaryStrings[0] == null) {
            legalStrings[0] = language[0][0];
            for (int j = 0; j < 20; j++) {
                legalStrings[j] = language[0][0].repeat(rand.nextInt(1,100));
            }
        }

        // Prints only one legal string if all the exponents are constant
        if (Objects.equals(legalStrings[0], legalStrings[1])) {
            System.out.println("1. " + legalStrings[0]);
        }
        // Prints all the 20 legal strings for the language
        else {
            for (int i = 0; i < legalStrings.length; i++) {
            System.out.println(i+1 + ". " + legalStrings[i]);
        }
        }

        // Returns the legal strings
        return legalStrings;
    }

    // Validates everything single constant variables (because the non-constant variables are <0)
    // Ex: a^2b^mc^3d^n (it validates that there is aa and ccc in the combinations)
    public static void validateCombinations(String[] legalStrings, String[][] language, int length) {
        String[] variableList = new String[length];
        int counter = 0;
        while (language[counter][1] != null) {
            variableList[counter] = language[counter][1];
            counter++;
        }

        counter = 0;
        for (int i = 0; i < 20; i++) {
            if (legalStrings[0] != null) {
                // If the exponent is a letter, skip it
                while (counter<variableList.length) {
                    if (Character.isLetter(language[counter][1].charAt(0))) {
                        counter++;
                    }
                    // Else check how many letters that the constants said it was a^2 (2) and return true or false.
                    else {
                        System.out.println(legalStrings[i].contains(language[counter][0].repeat(Integer.parseInt(language[counter][1]))));
                        System.out.println("^ the result that all the substrings contain the following: " + language[counter][0].repeat(Integer.parseInt(language[counter][1])));
                        counter++;
                    }
                    }
            }
        }
    }

    // Function that asks for the language format string and separates the format into [letter] [variable]
    public static String[][] parseLanguage(char[] alphabet) {
        String[][] language = new String[20][2];
        String ui = getUI("Enter language format string: ");
        StringBuilder[] substrings = parseSubstring(alphabet, ui);
        int counter = 0;
        for (int i = 0; i < substrings.length; i++) {
            if (substrings[i] != null) { // we need to parse
                language[counter][0] = substrings[i].substring(0, 1);
                language[counter][1] = substrings[i].substring(2, substrings[i].length());
                counter++;
            }
        }
        return language;
    }

    // Function that parses the language format string into one, example (a^2)
    public static StringBuilder[] parseSubstring(char[] alphabet, String ui) {
        StringBuilder[] substrings = new StringBuilder[ui.length()];
        int builderIndex = -1;
        for (int i = 0; i < ui.length(); i++) {
            if (inAphla(alphabet, ui.charAt(i))) {
                builderIndex++;
                substrings[builderIndex] = new StringBuilder();
            }
            substrings[builderIndex].append(ui.charAt(i));
        }
        return substrings;
    }

    // Function that returns true of false whether a character is in the alphabet or not.
    public static boolean inAphla(char[] aphla, char test) {
        boolean in = false;
        for (int i = 0; i < aphla.length; i++) {
            if (aphla[i] == test) {
                in = true;
            }
        }
        return in;
    }
}
