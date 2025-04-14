import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DFA {

    // Initialize variables
    private State[] stateList;
    private char[] alphabet;
    private State startState;


    // Constructors
    public DFA(){
        this.intialize();
    }

    public void intialize() {
        // Open File and read
        String DFAConfig = this.getFileContent();
        parseAlphabet(DFAConfig);
        // Get alphabet
    }

    // Grabs the file content
    private String getFileContent() {
        StringBuilder temp = new StringBuilder();
        try {
            File inFile = new File("config.yml");
            Scanner fileReader = new Scanner(inFile);
            while(fileReader.hasNext()) {
                temp.append(fileReader.nextLine() + "\n");
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found!!");
        }
        return temp.toString();
    }

    // Parses the and prints it out in the command terminal
    private void parseAlphabet(String config) {
        String[] stringList = config.split("\n");
        try {
            System.out.println("Alphabet / "+ stringList[1]);
        }catch (IndexOutOfBoundsException e) {
            System.out.println("Invalid config");
        }
    }

    // Getters
    public State[] getStateList(){
        return this.stateList;
    }

    public char[] getAlphabet() {
        return this.alphabet;
    }

    public State getStartState() {
        return this.startState;
    }


    // Setters
    public void setStateList(State[] stateList) {
        this.stateList = stateList;
    }

    public void setAlphabet(char[] alphabet) {
        this.alphabet = alphabet;
    }

    public void setStartState(State startState) {
        this.startState = startState;
    }

    // To String
    @Override
    public String toString() {
        return this.getAlphabet().toString();
    }
}