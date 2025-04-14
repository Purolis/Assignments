import java.util.Scanner;
import java.util.concurrent.TimeUnit;


public class Main {
    public static void main(String[] strSp) throws InterruptedException {
        // Go through the DFA and file to print the alphabet
        NFA newNFA = new NFA();

        //  Initialize the states
        State s0 = new State(0, false);
        State s1 = new State(1, false);
        State s2 = new State(2, true);
        State s3 = new State(3, false);

        // Add transitions to the states
        s0.addTransition(s1, 'a');
        s0.addTransition(s2, 'c');
        s1.addTransition(s2, 'b');
        s1.addTransition(s3, 'b');
        s3.addTransition(s2, 'a');

        // Starter code and also gives the String list from the user input
        String[] strSplit = starterCode();


        // Initialize variables needed to do the while loop.
        int counter = 0;
        int nfaCounter = 0;
        int stateNum = 0;
        int tempNum = 0;
        int nfaTempNum = 0;
        int[] multiplePaths = new int[2];
        boolean finalStateUser = false;
        boolean finalStateUserNFA = false;
        State nextState = s0;
        State temp = new State(100000, false);
        State nfaTemp = new State(10000, false);

        // While loop that goes through the strings and validates everything
        while (counter < strSplit.length) {

            // Simple print statements to show the user what state, transitions, and character is going through validation
            System.out.println("\n***** Current State Number " + stateNum + " *****");
            System.out.println("\tCharacter:"+strSplit[counter]);
            System.out.println("\tTransitions:");

            // Goes through the states and character is in transList, move on
            for (int j = 0; j < nextState.getTransList().length; j++) {
                System.out.println("\t" + nextState.getTransList()[j]);
                String transitions = String.valueOf(nextState.getTransList()[j]);
                if (transitions.contains(strSplit[counter])) {
                    multiplePaths[nfaCounter] = nfaCounter;
                    temp = nextState.getTransList()[j].getNextState();
                    tempNum = temp.getStateNum();
                    nfaCounter++;
                }
                if (multiplePaths[1] > 0) {
                    nfaTemp = nextState.getTransList()[0].getNextState();
                    nfaTempNum = nfaTemp.getStateNum();
                }
            }


            TimeUnit.SECONDS.sleep(2);

            // If the character isn't in transList, print Invalid.
            if (tempNum == 0) {
                System.out.println("Invalid!");
                break;
            }

            // Sets the next state and next number as temp and set the temp back to nothing for the next loop.
            nextState = temp;
            stateNum = tempNum;
            finalStateUser = nextState.getIsFinal();
            temp = new State(1000000, false);
            tempNum = 0;
            nfaCounter = 0;
            counter++;
        }

        // If there's any multiple paths in the config, our example is (q1 -> q2 q1 -> q3)
        if (multiplePaths[1] > 0) {
            counter = nfaTempNum;
            nextState = nfaTemp;
            stateNum = nfaTempNum;
            System.out.println("\n***** Moving onto the first choice ******");
            while (counter < strSplit.length) {

                // Simple print statements to show the user what state, transitions, and character is going through validation
                System.out.println("\n***** Current State Number " + stateNum + " *****");
                System.out.println("\tCharacter:" + strSplit[counter]);
                System.out.println("\tTransitions:");

                // Goes through the states and character is in transList, move on
                for (int j = 0; j < nextState.getTransList().length; j++) {
                    System.out.println("\t" + nextState.getTransList()[j]);
                    String transitions = String.valueOf(nextState.getTransList()[j]);
                    if (transitions.contains(strSplit[counter])) {
                        temp = nextState.getTransList()[j].getNextState();
                        tempNum = temp.getStateNum();
                    }
                }

                TimeUnit.SECONDS.sleep(2);

                // If the character isn't in transList, print Invalid.
                if (tempNum == 0) {
                    System.out.println("Invalid!");
                    break;
                }

                // Sets the next state and next number as temp and set the temp back to nothing for the next loop.
                nextState = temp;
                stateNum = tempNum;
                finalStateUserNFA = nextState.getIsFinal();
                temp = new State(1000000, false);
                tempNum = 0;
                counter++;
            }

            // Checks if nfaTempNum is = length of our string if so, check if it's final if it is process valid.
            if (nfaTempNum == strSplit.length) {
                System.out.println("\n***** Current State Number " + stateNum + " *****");
                System.out.println("\tCharacter:" + strSplit[stateNum-1]);
                System.out.println("\tTransitions:");
                finalStateUserNFA = nextState.getIsFinal();

                // Goes through the states and character is in transList, move on
                for (int j = 0; j < nextState.getTransList().length; j++) {
                    System.out.println("\t" + nextState.getTransList()[j]);

                }
            }
        }


        // Final validation tests to see if the last state given is a final state.
        if (finalStateUser == false && finalStateUserNFA == false) {
            System.out.println("\n****** Final Valid Test: Invalid ******");
        } else {
            System.out.println("\n****** Final Valid Test: Valid ******");
        }
    }

    public static String[] starterCode() {
        // Scanner to grab userInput string
        Scanner keyboard = new Scanner(System.in);

        // Added spaces for the language definition for readability, language definition
        System.out.println("Language Definition: L = {a^n c^m b^l b^z a^l} : n != m, {m,n} <= 1, l != z, m != {l,z}, {z,l} <= 1");


        // Grabs user input for the string
        System.out.println("\nChoose a string that fits it, if it doesn't it will tell you!");
        System.out.print("\tGive me a string that you'd like to validate: ");
        String userInput = keyboard.nextLine();

        // Splits the string into a list to go through every character.
        String[] strSplit = userInput.split("");

        return strSplit;
    }
}
