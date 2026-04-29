enum class InstructionType {

    rFormat, iFormat, sFormat, bFormat, jFormat, uFormat


};


struct instruction {

    //no need for character array since this is after decoding we only need 
    //integer values
    int opcode;
    int rd;
    int rs1;
    int rs2;
    int immediate;
    InstructionType type;


};

