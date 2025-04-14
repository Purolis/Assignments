public class Transition {

    // Initialize the variables
    private State nextState;
    private char transChar;


    // Constructors
    public Transition(State nextState, char transChar) {
        this.setNextState(nextState);
        this.setTransChar(transChar);
    }


    // Getters
    public State getNextState() {
        return this.nextState;
    }

    public char getTransChar() {
        return this.transChar;
    }

    // Setters
    public void setNextState(State nextState) {
        this.nextState = nextState;
    }

    public void setTransChar(char transChar) {
        this.transChar = transChar;
    }


    // To String
    @Override
    public String toString() {

        // Returns the transition character with the state
        return this.getTransChar() + " -> " + this.getNextState().toString();
    }
}