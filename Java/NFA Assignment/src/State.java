public class State {

    // Initialize the variables
    private Transition[] transList;
    private int stateNum;
    private boolean isFinal;


    // Constructors
    public State(int stateNum, boolean isFinal) {
        this.setStateNum(stateNum);
        this.setFinal(isFinal);
        this.setTransList(new Transition[0]);
    }


    // Transition function that adds the actual state with its transition character and the next state.
    public void addTransition(State newState, char transChar) {
        Transition[] temp = new Transition[this.getTransList().length + 1];
        for (int i = 0; i < this.getTransList().length; i++) {
            temp[i] = this.getTransList()[i];
        }
        temp[temp.length - 1] = new Transition(newState, transChar);
        this.setTransList(temp);
    }


    // Getters
    public Transition[] getTransList() {
        return this.transList;
    }

    public int getStateNum() {
        return this.stateNum;
    }

    public boolean getIsFinal() {
        return this.isFinal;
    }


    // Setters
    public void setTransList(Transition[] transList) {
        this.transList = transList;
    }

    public void setStateNum(int stateNum) {
        this.stateNum = stateNum;
    }

    public void setFinal(boolean aFinal) {
        isFinal = aFinal;
    }


    // To string
    @Override
    public String toString() {

        // Prints the state number Q0, Q1, etc...
        return "Q" + this.getStateNum();
    }
}