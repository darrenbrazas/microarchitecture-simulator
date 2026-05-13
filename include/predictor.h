struct BranchPredictor {

    int counter = 0b01;

    bool predict() {

        return counter >= 2; //predict its been taken if binary number is 10 (2)
    }

    void update (bool taken) {

        
    }
};